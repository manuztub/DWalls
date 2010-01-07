#include "dwalls.h"
#include "ui_dwalls.h"
#include <QFileDialog>
#include <QtGui>
#include <QLineEdit>
#include <QDir>
#include <QFile>

Dwalls::Dwalls(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dwalls)
{
    ui->setupUi(this);
}

Dwalls::~Dwalls()
{
    delete ui;
}

void Dwalls::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dwalls::on_actionEsci_triggered()
{
    exit(1);
}

void Dwalls::on_toolButton_3_clicked()
{
    QString f;
    f=QFileDialog::getExistingDirectory(this, tr("Apri Cartella"),"/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit->setText(f);
    QDir cartella(f);
    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.gif";
    //dir.setNameFilters(filters);
    QStringList list = cartella.entryList(filters, QDir::Files,QDir::Unsorted);
    foreach (QString k, list)
        {
            ui->listFile->addItem(k);
        }
}

void Dwalls::on_lineEdit_returnPressed()
{

}

void Dwalls::on_pushButton_2_clicked()
{
    QStringList f;
    f=QFileDialog::getOpenFileNames(this,"Aggiungi File","/","Immagini (*.png *.gif *.jpg)");
    QStringList list = f;
    QStringList::Iterator it = list.begin();
    foreach (QString k, list)
        {
            ui->listFile->addItem(k);
        }
}

void Dwalls::on_pushButton_clicked()
{
    QString grt= ui->lineEdit->text()+"background.xml";
    QFile file("background.xml");
    int m=ui->comboBox_4->currentIndex();
    switch (m)
            {
            case 0:m=30;
        break;
            case 1:m=60;
        break;
            case 2:m=300;
        break;
            case 3:m=600;
        break;
            case 4:m=1200;
        break;
            case 5:m=1800;
        break;
            case 6:m=3600;
        break;
            case 7:m=7200;
        break;
            case 8:m=10800;
        break;
            case 9:m=14400;
        break;
            case 10:m=18000;
        break;
    }
    int n=ui->comboBox_3->currentIndex();
    switch (m)
            {
            case 0:n=1;
        break;
            case 1:n=2;
        break;
            case 2:n=5;
        break;
            case 3:n=7;
        break;
            case 4:n=10;
        break;
            case 5:n=20;
        break;
    }
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "<background>\n<starttime>\n<year>2009</year>\n<month>08</month>\n<day>04</day>\n<hour>00</hour>\n<minute>00</minute>\n<second>00</second>\n</starttime>";
    int i=ui->listFile->count();
    QStringList l;
    QListWidgetItem* r;
    for (int j=0;j<i;j++)
    {
        r=ui->listFile->takeItem(j);
        l+=r->text();
    }
    stream << "\n<static>";
    stream <<"\n<duration>"<< m<<".0</duration>";
    stream <<"\n<file>"<< l.first()<<"</file>";
    stream <<"\n</static>";
    stream <<"\n<transition>";
    stream <<"\n<duration>"<< n <<".0</duration>";
    stream <<"\n<from>"<< l.first()<<"</from>";
    foreach(QString u, l)
    {
        stream <<"\n<to>"<< u <<"</to>";
        stream <<"\n</transition>";
        stream << "\n<static>";
        stream <<"\n<duration>"<< m <<".0</duration>";
        stream <<"\n<file>"<< u <<"</file>";
        stream <<"\n</static>";
        stream <<"\n<transition>";
        stream <<"\n<duration>"<< n <<".0</duration>";
        stream <<"\n<from>"<< u <<"</from>";
    }
    stream << "\n<to>"<< l.first() <<"</to>";
    stream << "\n</transition>";
    stream << "\n</transition>\n</background>" << endl;
    ui->label_6->setText("File generato con successo "+ file.fileName());
    file.close();

}
