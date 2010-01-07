#ifndef DWALLS_H
#define DWALLS_H

#include <QMainWindow>

namespace Ui {
    class Dwalls;
}

class Dwalls : public QMainWindow {
    Q_OBJECT
public:
    Dwalls(QWidget *parent = 0);
    ~Dwalls();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Dwalls *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();
    void on_toolButton_3_clicked();
    void on_actionEsci_triggered();
    void on_actionAbout_triggered();
};

#endif // DWALLS_H
