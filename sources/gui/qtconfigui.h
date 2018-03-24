#ifndef QTCONFIGUI_H
#define QTCONFIGUI_H
#include <configui.h>

using BootPrints::Interfaces::ConfigUI<QWidget> = QtConfigUI;

#define QtConfigUI_iid "org.Akooos.BootPrints.QtConfigUI"
Q_DECLARE_INTERFACE(QtConfigUI, QtConfigUI_iid)

#endif // QTCONFIGUI_H
