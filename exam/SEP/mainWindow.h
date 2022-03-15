#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#endif // MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "battlefield.h"
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    BattleField battle_field;
    QColor enemy_color;
    QColor safe_color;
    QColor path_color;
public:
    MainWindow(QWidget *parent = nullptr);
    // use data in the file to init the battle field
    void load_data();
    void createActions();
    void createMenus();
    void findWay();
    QAction *loadDataAction;
    QAction *searchAction;
    QPushButton load;
    QPushButton search;
protected:
    // draw battle field
    void paintEvent(QPaintEvent *event) override;
    // listen to the key press event
    void keyPressEvent(QKeyEvent *event) override;

};
