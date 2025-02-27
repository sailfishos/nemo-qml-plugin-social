#include <QtCore/QDir>
#include <QtQml>
#include <QQuickItem>
#include <QQuickView>
#include <QGuiApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    if (argc != 2) {
        qWarning() << "usage: facebooktest [facebook_access_token]";
        return 1;
    }

    // TODO: manage better the difference between desktop and device
    view.engine()->addImportPath(PLUGIN_PATH);
    view.setSource(QUrl::fromLocalFile(QLatin1String("share/facebooksocialtest.qml")));

    if (view.status() == QQuickView::Error) {
        qWarning() << "Unable to read main qml file";
        return 1;
    }

    view.rootObject()->setProperty("accessToken", QLatin1String(argv[1]));
    view.rootObject()->setProperty("_desktop", true);
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    view.show();

    QObject::connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    return app.exec();
}

