#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>


class PaintArea : public QWidget {
    Q_OBJECT

  public:
    explicit PaintArea(QWidget* parent = nullptr)
            : QWidget(parent) {
    }

  protected:
    void mouseMoveEvent(QMouseEvent* event) {
        touchpoints.append(event->pos());
        update();
    }

    void paintEvent(QPaintEvent* event) {
        Q_UNUSED(event);

        QPainter p { this };
        p.fillRect(0, 0, width(), height(), Qt::white);
        for (int i = 0; i < touchpoints.count(); i++) {
            if (i + 1 >= touchpoints.count())
                break;

            p.drawLine(touchpoints.at(i), touchpoints.at(i + 1));
        }
    }

    void keyReleaseEvent(QKeyEvent* ev) {
        if (ev->key() == Qt::Key_Q)
            qApp->quit();
    }

  private:
    QVector<QPoint> touchpoints;
};

#include "main.moc"


int main(int argc, char** argv) {
    QApplication app { argc, argv };

    PaintArea window { nullptr };
    window.show();

    return app.exec();
}
