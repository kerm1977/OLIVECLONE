/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2022 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#include "importdialog.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfoList>
#include <QHeaderView>
#include <QPushButton>
#include <QStandardPaths>
#include <QStorageInfo>

namespace olive {

ImportDialog::ImportDialog(QWidget* parent)
  : QDialog(parent)
{
  SetupUI();
  SetupFileSystem();
  SetupUserFolders();
  SetupDrives();
  RetranslateUI();
}

void ImportDialog::SetupUI()
{
  setWindowTitle(tr("Importar Archivos"));
  resize(900, 600);

  QVBoxLayout* main_layout = new QVBoxLayout(this);

  // Top section: Look in label and path combo
  QHBoxLayout* top_layout = new QHBoxLayout();
  look_in_label_ = new QLabel(this);
  file_name_edit_ = new QLineEdit(this);
  file_name_edit_->setReadOnly(true);
  top_layout->addWidget(look_in_label_);
  top_layout->addWidget(file_name_edit_);
  main_layout->addLayout(top_layout);

  // Middle section: Splitter with folder tree and file list
  splitter_ = new QSplitter(Qt::Horizontal, this);

  // Folder tree view (left panel)
  folder_model_ = new QFileSystemModel(this);
  folder_model_->setRootPath(QDir::rootPath());
  folder_model_->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Drives);

  folder_tree_ = new QTreeView(this);
  folder_tree_->setModel(folder_model_);
  folder_tree_->setHeaderHidden(true);
  folder_tree_->hideColumn(1); // Size
  folder_tree_->hideColumn(2); // Type
  folder_tree_->hideColumn(3); // Date
  folder_tree_->hideColumn(4); // Permissions

  // File list view (right panel)
  file_model_ = new QFileSystemModel(this);
  file_model_->setRootPath(QDir::homePath());
  file_model_->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);

  file_list_ = new QListView(this);
  file_list_->setModel(file_model_);
  file_list_->setViewMode(QListView::ListMode);
  file_list_->setSelectionMode(QAbstractItemView::ExtendedSelection);

  splitter_->addWidget(folder_tree_);
  splitter_->addWidget(file_list_);
  splitter_->setStretchFactor(0, 1);
  splitter_->setStretchFactor(1, 3);

  main_layout->addWidget(splitter_);

  // Bottom section: File name, file type, and buttons
  QHBoxLayout* bottom_layout = new QHBoxLayout();
  
  file_name_label_ = new QLabel(this);
  file_name_edit_ = new QLineEdit(this);
  file_type_label_ = new QLabel(this);
  file_type_combo_ = new QComboBox(this);
  file_type_combo_->addItem(tr("Todos los archivos (*)"));
  
  bottom_layout->addWidget(file_name_label_);
  bottom_layout->addWidget(file_name_edit_);
  bottom_layout->addWidget(file_type_label_);
  bottom_layout->addWidget(file_type_combo_);
  
  main_layout->addLayout(bottom_layout);

  // Button box
  button_box_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  button_box_->button(QDialogButtonBox::Ok)->setText(tr("Abrir"));
  button_box_->button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));
  main_layout->addWidget(button_box_);

  connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);

  // Connect folder selection to file list
  connect(folder_tree_->selectionModel(), &QItemSelectionModel::currentChanged,
          this, [this](const QModelIndex& current, const QModelIndex& previous) {
            if (current.isValid()) {
              QString path = folder_model_->filePath(current);
              current_path_ = path;
              file_name_edit_->setText(path);
              UpdateFileList(path);
            }
          });
          
  // Connect file selection to file name edit
  connect(file_list_->selectionModel(), &QItemSelectionModel::selectionChanged,
          this, [this](const QItemSelection& selected, const QItemSelection& deselected) {
            QModelIndexList indexes = selected.indexes();
            if (!indexes.isEmpty()) {
              QString file_path = file_model_->filePath(indexes.first());
              file_name_edit_->setText(file_path);
            }
          });
}

void ImportDialog::SetupFileSystem()
{
  // Set root to show all drives on Linux
  QString root_path = QDir::rootPath();
  QModelIndex root_index = folder_model_->setRootPath(root_path);
  folder_tree_->setRootIndex(root_index);
  
  current_path_ = QDir::homePath();
  file_name_edit_->setText(current_path_);
}

void ImportDialog::SetupUserFolders()
{
  QString home_path = QDir::homePath();
  
  // The folder tree will automatically show user folders when expanded
  // We just need to ensure the home directory is visible
  QModelIndex home_index = folder_model_->index(home_path);
  if (home_index.isValid()) {
    folder_tree_->expand(home_index);
  }
}

void ImportDialog::SetupDrives()
{
  // On Linux, get mounted drives from /media and /mnt
  QStringList drive_paths;
  
  QDir media_dir("/media");
  if (media_dir.exists()) {
    QFileInfoList media_list = media_dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo& info : media_list) {
      drive_paths.append(info.absoluteFilePath());
    }
  }
  
  QDir mnt_dir("/mnt");
  if (mnt_dir.exists()) {
    QFileInfoList mnt_list = mnt_dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo& info : mnt_list) {
      drive_paths.append(info.absoluteFilePath());
    }
  }
  
  // Also check for mount points using QStorageInfo
  QList<QStorageInfo> storage_list = QStorageInfo::mountedVolumes();
  for (const QStorageInfo& storage : storage_list) {
    if (storage.isValid() && storage.isReady()) {
      QString mount_point = storage.rootPath();
      if (!drive_paths.contains(mount_point) && mount_point != "/") {
        drive_paths.append(mount_point);
      }
    }
  }
  
  // Expand drives in the tree view
  for (const QString& drive_path : drive_paths) {
    QModelIndex drive_index = folder_model_->index(drive_path);
    if (drive_index.isValid()) {
      folder_tree_->expand(drive_index);
    }
  }
}

void ImportDialog::LoadUserFolder(const QString& path, const QString& name)
{
  QDir dir(path);
  if (dir.exists()) {
    // The folder tree will automatically show these folders
  }
}

void ImportDialog::UpdateFileList(const QString& path)
{
  QDir dir(path);
  if (dir.exists()) {
    file_list_->setRootIndex(file_model_->setRootPath(path));
  }
}

void ImportDialog::RetranslateUI()
{
  look_in_label_->setText(tr("Buscar en:"));
  file_name_label_->setText(tr("Nombre de archivo:"));
  file_type_label_->setText(tr("Tipo de archivo:"));
  file_type_combo_->setItemText(0, tr("Todos los archivos (*)"));
  button_box_->button(QDialogButtonBox::Ok)->setText(tr("Abrir"));
  button_box_->button(QDialogButtonBox::Cancel)->setText(tr("Cancelar"));
  setWindowTitle(tr("Importar Archivos"));
}

QStringList ImportDialog::GetSelectedFiles() const
{
  QStringList selected_files;
  QModelIndexList selected_indexes = file_list_->selectionModel()->selectedIndexes();

  for (const QModelIndex& index : selected_indexes) {
    if (index.column() == 0) { // Only get each file once
      QString file_path = file_model_->filePath(index);
      QFileInfo file_info(file_path);
      if (file_info.isFile()) {
        selected_files.append(file_path);
      }
    }
  }

  return selected_files;
}

} // namespace olive
