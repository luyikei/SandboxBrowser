#include "sandboxbrowser.h"
#include "ui_sandboxbrowser.h"

#include <QProcess>

#include <QX11EmbedWidget>
#include <QVBoxLayout>
#include <QtGui>
#include <QDebug>

#include <sys/time.h>
#include <sys/resource.h>

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
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    qDebug() << QString("RLIMIT_STACK cur %1 max %2").arg(rl.rlim_cur).arg(rl.rlim_max);

    getrlimit(RLIMIT_DATA, &rl);
    qDebug() << QString("RLIMIT_DATA cur %1 max %2").arg(rl.rlim_cur).arg(rl.rlim_max);

    getrlimit(RLIMIT_AS, &rl);
    qDebug() << QString("RLIMIT_AS cur %1 max %2").arg(rl.rlim_cur).arg(rl.rlim_max);

    QX11EmbedContainer *container = new QX11EmbedContainer(ui->tabWidget);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->tabWidget->insertTab(ui->tabWidget->currentIndex() + 1, container, "test");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);

    SandBoxProcess* process = new SandBoxProcess(container);
    processes.insert(ui->tabWidget->currentIndex(), process);
    arguments << QString::number(container->winId());
    process->start(executable, arguments);
}

void SandboxBrowser::on_newBadChild_clicked()
{
    QStringList arguments;
    startProcessInTab("../build-SandboxBrowserBadChildProcess-Qt_4-Debug/SandboxBrowserBadChildProcess", arguments);
}
