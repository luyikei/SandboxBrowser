#include "sandboxbrowser.h"
#include "ui_sandboxbrowser.h"

#include <QProcess>

#include <QX11EmbedWidget>
#include <QVBoxLayout>
#include <QtGui>

#include "sandboxprocess.h"


SandboxBrowser::SandboxBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SandboxBrowser)
{
    ui->setupUi(this);



}

SandboxBrowser::~SandboxBrowser()
{
    delete ui;
}

void SandboxBrowser::on_newTabButton_clicked()
{

    QStringList arguments;
    startProcessInTab("../build-SandboxBrowserChildProcess-Qt_4-Debug/SandboxBrowserChildProcess", arguments);
}

void SandboxBrowser::on_terminalButton_clicked()
{


    QStringList arguments;
    arguments << "-into";
    startProcessInTab("xterm", arguments);


}

void SandboxBrowser::on_tabWidget_tabCloseRequested(int index)
{
    processes.at(index)->kill();
    processes.removeAt(index);

    ui->tabWidget->removeTab(index);
}

void SandboxBrowser::startProcessInTab(const QString &executable, QStringList &arguments)
{

    QX11EmbedContainer *container = new QX11EmbedContainer(ui->tabWidget);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tabWidget->insertTab(ui->tabWidget->currentIndex() + 1, container, "test");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);

    SandBoxProcess* process = new SandBoxProcess(container);
    processes.insert(ui->tabWidget->currentIndex(), process);
    arguments << QString::number(container->winId());
    process->start(executable, arguments);
}
