#include "gallerywindow.h"
#include <QPixmap>
#include <QHBoxLayout>

GalleryWindow::GalleryWindow(QWidget *mainWindow, QWidget *parent)
    : QWidget(parent), mainMenu(mainWindow)
{
    setFixedSize(1024, 768);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *backButton = new QPushButton("Back to Menu");
    backButton->setStyleSheet("font-size: 16px; padding: 8px;");
    layout->addWidget(backButton, 0, Qt::AlignLeft);

    connect(backButton, &QPushButton::clicked, this, [this]() {
        mainMenu->show();
        this->close();
    });

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *imageContainer = new QWidget();
    QHBoxLayout *imageLayout = new QHBoxLayout(imageContainer);

    QStringList imagePaths = {
        "image/soldier1.png",
        "image/soldier2.png",
        "image/soldier3.png"
    };

    for (const QString &path : imagePaths) {
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            QLabel *label = new QLabel();
            label->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            imageLayout->addWidget(label);
        }
    }

    imageContainer->setLayout(imageLayout);
    scrollArea->setWidget(imageContainer);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);
}
