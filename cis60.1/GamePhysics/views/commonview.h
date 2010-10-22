#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include <QGraphicsView>
#include <QTextEdit>

class CommonView : public QGraphicsView
{
    Q_OBJECT

public:
    CommonView(QGraphicsScene *scene,QWidget *parent);

    const QString getInstructions();

signals:

public slots:

};

#endif // COMMONVIEW_H
