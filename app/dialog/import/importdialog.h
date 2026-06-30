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

#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFileSystemModel>
#include <QListView>
#include <QSplitter>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

namespace olive {

class ImportDialog : public QDialog
{
  Q_OBJECT
public:
  ImportDialog(QWidget* parent = nullptr);
  QStringList GetSelectedFiles() const;

private:
  void SetupUI();
  void SetupFileSystem();
  void SetupUserFolders();
  void SetupDrives();
  void LoadUserFolder(const QString& path, const QString& name);
  void UpdateFileList(const QString& path);
  void RetranslateUI();

  QSplitter* splitter_;
  QTreeView* folder_tree_;
  QListView* file_list_;
  QFileSystemModel* folder_model_;
  QFileSystemModel* file_model_;
  QDialogButtonBox* button_box_;
  
  QLabel* look_in_label_;
  QLabel* file_name_label_;
  QLabel* file_type_label_;
  QLineEdit* file_name_edit_;
  QComboBox* file_type_combo_;
  
  QString current_path_;
};

} // namespace olive

#endif // IMPORTDIALOG_H
