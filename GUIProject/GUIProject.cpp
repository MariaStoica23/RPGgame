#include "ui_guiproject.h"
#include "GUIProject.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), showingFirst(true)
{
    ui->setupUi(this);

    img1.load("image1.png");
    img2.load("image2.png");

    ui->imageLabel->setPixmap(img1);

    //connect(ui->toggleButton, &QPushButton::clicked, this, &MainWindow::on_toggleButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toggleButton_clicked()
{
    if (showingFirst) {
        ui->imageLabel->setPixmap(img2);
    }
    else {
        ui->imageLabel->setPixmap(img1);
    }
    showingFirst = !showingFirst;
}