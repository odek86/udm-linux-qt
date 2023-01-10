#include "adddialog.h"

AddDialog::AddDialog() : QDialog(), ui(new Ui::AddDialog) {
    ui->setupUi(this);
    this->setFixedSize(width(), height());
    QClipboard *k = QApplication::clipboard();
    QUrl tempUrl = k->text();

    if(tempUrl.isValid()) {
        qDebug("URL: %s", qUtf8Printable(tempUrl.toString()));

        ui->txtName->setText(tempUrl.fileName());
        ui->lineEdit->setText(tempUrl.toString());
        ui->btnOK->setEnabled(true);

        ui->txtSave->setText(getOutDirectory());
    }
}



AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::on_btnOK_clicked() {
    fileGlobal = new DownloadFile(url);
    fileGlobal->resumable = ui->checkBox->isChecked();
    fileGlobal->miscArgs = ui->lineEdit_2->text();
    start = ui->chkStart->isChecked();
    if (ui->chkName->isChecked()) {
        fileGlobal->outDir = ui->txtSave->text();
    } else {
        fileGlobal->fullPath = ui->txtSave->text() + QDir::separator() + ui->txtName->text();
    }
    this->accept();
}

void AddDialog::on_lineEdit_textChanged(const QString &arg1) {
    url = ui->lineEdit->text();
    if (QUrl(url).isValid()){
        ui->txtName->clear();
        QString fileName(QUrl(url).fileName());
        ui->txtName->setText(fileName);
    }
    ui->btnOK->setEnabled(QUrl(arg1).isValid());
}

void AddDialog::on_btnCancel_clicked() {
    this->reject();
}

void AddDialog::on_checkBox_2_clicked() {
    bool enable = !(ui->checkBox_2->isChecked());
    ui->btnSave->setEnabled(enable);
    ui->txtSave->setEnabled(enable);
    ui->lblSave->setEnabled(enable);
    if(!enable) {
        ui->txtSave->setText(::getOutDirectory());
    }
}

void AddDialog::on_btnSave_clicked() {
    QString tempSave = QFileDialog::getExistingDirectory(this, "Open Directory", ui->txtSave->text(), QFileDialog::ShowDirsOnly);
    if (!(tempSave == "")) {
        ui->txtSave->setText(tempSave);
    }
}

void AddDialog::on_chkName_clicked() {
    bool enable = !(ui->chkName->isChecked());
    ui->txtName->setEnabled(enable);
    ui->lblName->setEnabled(enable);
    ui->btnOK->setEnabled(!enable);
}

void AddDialog::on_txtName_textChanged(const QString &arg1) {
    ui->btnOK->setEnabled(!arg1.isEmpty());
}

void AddDialog::on_lineEdit_editingFinished()
{

}

