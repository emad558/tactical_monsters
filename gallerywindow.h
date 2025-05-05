#ifndef GALLERYWINDOW_H
#define GALLERYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>

class GalleryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GalleryWindow(QWidget *mainWindow, QWidget *parent = nullptr);

private:
    QWidget *mainMenu;
};

#endif // GALLERYWINDOW_H
