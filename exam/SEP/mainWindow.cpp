#include "mainWindow.h"
#include <QGraphicsView>
#include <QTimer>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // set window title
    setWindowTitle(tr("Find Way To Exit!!!"));
    // @TODO write your codes here
    setFixedSize(650, 520);
    enemy_color.setRgb(205, 92, 92);
    safe_color.setRgb(0, 255, 127);
    path_color.setRgb(138, 43, 226);
    load.setParent(this);
    search.setParent(this);
    load.setText("Load Data");
    search.setText("Search");
    load.move(20, 25);
    search.move(20, 100);
    connect(&load, &QPushButton::clicked, this, &MainWindow::load_data);
    connect(&search, &QPushButton::clicked, this, &MainWindow::findWay);
    load.show();
    search.show();
}

void MainWindow::load_data()
{
    // @TODO write your codes here
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ":/", tr("*.txt"));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream fin(&file);
    int n, fx, fy, tx, ty;
    fin >> n;
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
            battle_field.field[x][y] = 0;
    }
    for (int x = 1; x <= n; x++)
    {
        fin >> fx >> fy >> tx >> ty;
        for (int i = fx; i <= tx; i++)
        {
            for (int j = fy; j <= ty; j++)
                battle_field.field[i][j] = 1;
        }
    }
    file.close();
    update();
}

void MainWindow::findWay()
{
    if (!battle_field.findPath())
    {
        QMessageBox::information(NULL, tr("Error"), tr("Can not find path."), QMessageBox::Yes, QMessageBox::Yes);
    }
    else
    {
        update();
        QTextStream fout(stdout);
        for (int x = 1; x <= battle_field.top; x++)
        {
            fout << battle_field.sta[x][0] << " " << battle_field.sta[x][1] << endl;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // @TODO write your codes here
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // @TODO write your codes here
    QPainter painter(this);
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            const QPoint Box[4] = {
                QPoint(5 * x + 150, 510 - 5 * y),
                QPoint(5 * x + 150, 510 - 5 * y - 5),
                QPoint(5 * x + 5 + 150, 510 - 5 * y - 5),
                QPoint(5 * x + 5 + 150, 510 - 5 * y)};
            if (battle_field.field[x][y] == 1)
                painter.setBrush(enemy_color);
            if (battle_field.field[x][y] == 2)
                painter.setBrush(path_color);
            if (battle_field.field[x][y] == 0)
                painter.setBrush(safe_color);
            painter.drawConvexPolygon(Box, 4);
        }
    }
}
