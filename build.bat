set QT_DIR=C:\Qt-6.6.1
set Qt6_DIR=%QT_DIR%
xmake f -y --qt=%QT_DIR% -p windows -a x64
xmake b -y