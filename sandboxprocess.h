#ifndef SANDBOXPROCESS_H
#define SANDBOXPROCESS_H

#include <QProcess>

class SandBoxProcess : public QProcess
{
    Q_OBJECT
public:
    explicit SandBoxProcess(QObject *parent = 0);

signals:

public slots:

protected:
    void setupChildProcess();
};

#endif // SANDBOXPROCESS_H
