#ifndef SCREENCAPT_H
#define SCREENCAPT_H

#include <QWidget>

class screenCapt : public QWidget
{
    Q_OBJECT
public:
    explicit screenCapt(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SCREENCAPT_H