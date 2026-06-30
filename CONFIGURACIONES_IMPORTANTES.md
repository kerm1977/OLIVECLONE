# CONFIGURACIONES IMPORTANTES - NO CAMBIAR

## ⚠️ ADVERTENCIA IMPORTANTE ⚠️
**ESTE DOCUMENTO CONTIENE CONFIGURACIONES CRÍTICAS QUE NO DEBEN SER MODIFICADAS**
**POR NINGÚN MOTIVO SIN AUTORIZACIÓN EXPLÍCITA DEL USUARIO**

---

## 1. DIÁLOGO DE IMPORTACIÓN (QFileDialog Nativo)

### Configuración Actual:
- **Tipo**: QFileDialog nativo del sistema operativo
- **Función**: `QFileDialog::getOpenFileNames()` en `core.cpp`
- **Comportamiento**: Abre el gestor de archivos nativo según el sistema operativo:
  - **Peppermint OS**: Thunar
  - **Lubuntu/LXQt/LXDE**: PCManFM
  - **GNOME**: Nautilus
  - **KDE**: Dolphin
  - **Otros**: El gestor de archivos correspondiente

### Importante:
- **NO** usar diálogo personalizado para importación
- **NO** intentar filtrar carpetas del sistema en diálogo nativo (no es posible)
- Las carpetas del sistema visibles en la raíz (Video, Music, Pictures, Documents, Downloads, Public, etc.) son mostradas por el gestor de archivos nativo y no pueden ser ocultadas desde la aplicación

### Archivos:
- `app/core.cpp` - Función `DialogImportShow()`

---

## 2. DIÁLOGO DE ABRIR PROYECTO (QFileDialog Nativo)

### Configuración Actual:
- **Tipo**: QFileDialog nativo del sistema operativo
- **Función**: `QFileDialog::getOpenFileName()` en `core.cpp`
- **Comportamiento**: Abre el gestor de archivos nativo según el sistema operativo

### Archivos:
- `app/core.cpp` - Función `OpenProject()`

---

## 3. DIÁLOGO DE GUARDAR PROYECTO (QFileDialog Nativo)

### Configuración Actual:
- **Tipo**: QFileDialog nativo del sistema operativo
- **Función**: `QFileDialog::getSaveFileName()` en `core.cpp`
- **Comportamiento**: Abre el gestor de archivos nativo según el sistema operativo

### Archivos:
- `app/core.cpp` - Función `SaveProjectAs()`

---

## 4. TRADUCCIONES DEL DIÁLOGO DE IMPORTACIÓN

### Configuración Actual:
- **Título**: "Importar Archivos..."
- **Elementos UI**: Los elementos del diálogo nativo (Look in, File Name, Files of Type, All files(*), Open, Cancel) se traducen automáticamente según el idioma del sistema operativo, no según el idioma configurado en Olive

### Importante:
- **NO** intentar traducir elementos del diálogo nativo desde la aplicación
- Las traducciones dependen del idioma del sistema operativo, no de la configuración de Olive

---

## 5. HERRAMIENTA DE CORTE (RAZOR TOOL)

### Configuración Actual:
- **Atajo de teclado**: X
- **Comportamiento**: Corta en la posición del playhead (línea azul de desplazamiento), no en la posición del mouse
- **Función**: La cuchilla de corte está adherida a la línea de tiempo y corta en el playhead

### Archivos:
- `app/widget/timelinewidget/tool/razor.cpp` - Funciones `MouseMove()` y `MouseRelease()`

### Importante:
- **NO** modificar para cortar en posición del mouse
- **NO** cambiar el atajo de teclado de X

---

## 6. ATAJO DE TECLADO DE ELIMINAR

### Configuración Actual:
- **Atajo de teclado**: D
- **Comportamiento**: Elimina elementos seleccionados

### Archivos:
- `app/widget/menu/menushared.cpp` - Línea 48

### Importante:
- **NO** cambiar el atajo de teclado de D

---

## 7. ATAJO DE TECLADO DE SELECCIONAR TODO

### Configuración Actual:
- **Atajo de teclado**: A (sin Ctrl)
- **Comportamiento**: Selecciona todos los elementos

### Archivos:
- `app/window/mainwindow/mainmenu.cpp` - Línea 95

### Importante:
- **NO** cambiar el atajo de teclado de A
- **NO** usar Ctrl+A

---

## 8. ATAJO DE TECLADO DE TRACK SELECT TOOL

### Configuración Actual:
- **Atajo de teclado**: T
- **Comportamiento**: Herramienta de selección de pista

### Archivos:
- `app/window/mainwindow/mainmenu.cpp` - Línea 207

### Importante:
- **NO** cambiar el atajo de teclado de T

---

## 9. ATAJO DE TECLADO DE EDIT TOOL

### Configuración Actual:
- **Atajo de teclado**: C
- **Comportamiento**: Herramienta de edición

### Archivos:
- `app/window/mainwindow/mainmenu.cpp` - Línea 212

### Importante:
- **NO** cambiar el atajo de teclado de C

---

## 10. ATAJO DE TECLADO DE TRANSITION TOOL

### Configuración Actual:
- **Atajo de teclado**: Y
- **Comportamiento**: Herramienta de transición

### Archivos:
- `app/window/mainwindow/mainmenu.cpp` - Línea 252

### Importante:
- **NO** cambiar el atajo de teclado de Y

---

## 11. ATAJO DE TECLADO DE ADD TOOL

### Configuración Actual:
- **Atajo de teclado**: Q
- **Comportamiento**: Herramienta de agregar

### Archivos:
- `app/window/mainwindow/mainmenu.cpp` - Línea 257

### Importante:
- **NO** cambiar el atajo de teclado de Q

---

## 12. IDIOMA POR DEFECTO

### Configuración Actual:
- **Idioma**: es_ES (Español)
- **Archivo**: `app/config/config.cpp` - Línea 76

### Importante:
- **NO** cambiar el idioma por defecto a inglés
- **NO** modificar la configuración de idioma sin autorización

---

## RESUMEN DE ATAJOS DE TECLADO PRINCIPALES

| Acción | Atajo | Archivo |
|--------|-------|---------|
| Corte (Razor Tool) | X | mainmenu.cpp línea 227 |
| Eliminar | D | menushared.cpp línea 48 |
| Seleccionar todo | A | mainmenu.cpp línea 95 |
| Track Select Tool | T | mainmenu.cpp línea 207 |
| Edit Tool | C | mainmenu.cpp línea 212 |
| Transition Tool | Y | mainmenu.cpp línea 252 |
| Add Tool | Q | mainmenu.cpp línea 257 |

---

## ⚠️ NOTA FINAL

**ESTE DOCUMENTO DEBE SER ACTUALIZADO CADA VEZ QUE SE REALICE UN CAMBIO EN LAS CONFIGURACIONES LISTADAS ARRIBA**

**CUALQUIER CAMBIO EN ESTAS CONFIGURACIONES SIN AUTORIZACIÓN EXPLÍCITA DEL USUARIO ESTÁ PROHIBIDO**
