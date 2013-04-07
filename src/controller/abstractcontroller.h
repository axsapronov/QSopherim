#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>
#include "src/model/abstractmodel.h"

class AbstractController : public QObject
{
    Q_OBJECT
public:
    explicit AbstractController(QObject *parent = 0);
    AbstractController(AbstractModel *model);

    void start()
      {
//          m_model->setC(0);

          float temp;
          int i = 0;
          do
          {
//              std::cin << ("%f", &temp);
              temp = 5.0;
              m_model->setC(temp);
              i++;
          }
          while (i != 1);
      }

signals:

private:
    AbstractModel* m_model;

public slots:

};

#endif // ABSTRACTCONTROLLER_H
