#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();
    this->setupModel(TABLE_TEACH, QStringList() << "id преподавателя"
                                               << "ФИО"
                                               << "Дата рождения"
                                               << "Должность"
                                               << "Кафедра");
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlRelationalTableModel(this);
    model->setTable(tableName);
    model->setRelation(4, QSqlRelation(TABLE_DEPARTMENT, DEP_ID, DEP_NAME));
    model->setRelation(3, QSqlRelation(TABLE_POSITION, POS_ID, POS_NAME));
    for (int i = 0, j = 0; i < model->columnCount(); i++, j++)
    {
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
    model->select();
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    model->select();
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    ui->tableView->setColumnHidden(0, !state);
}

void MainWindow::on_btnexit_clicked()
{
    this->close();
}

void MainWindow::on_btnabout_clicked()
{
    QMessageBox msgBox;
    msgBox.information(this, "О программе", "Это как ваша лабораторная работа №4, только меньше");
}

void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_pushButton_3_clicked()
{
    createUI();
}

