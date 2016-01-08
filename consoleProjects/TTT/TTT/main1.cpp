//
//#include <QObject>
//#include <QObject>
//#include <QtCore/QCoreApplication>
//
//class Filter;
//class KeyPressEater;
//
//
//class Filter : public QObject
//{
//    Q_OBJECT
//
//protected:
//    bool eventFilter(QObject *, QEvent *);
//};
//
//bool Filter::eventFilter(QObject *obj, QEvent *evt)
//{
//    Q_UNUSED(obj);
//    Q_UNUSED(evt);
//    return true;
//}
//
//class KeyPressEater : public QObject
//{
//    Q_OBJECT
//
//protected:
//    bool eventFilter(QObject *, QEvent *);
//};
//
//bool KeyPressEater::eventFilter (QObject *obj, QEvent *e)
//{
//    if (e->type() == QEvent::KeyPress) 
//    {
//        //qDebug ("Ate key press");
//        return true;
//    } 
//    else 
//    {
//        // standard event processing
//        return QObject::eventFilter(obj, e);
//    }
//    Q_UNUSED(obj);
//    Q_UNUSED(e);
//    return true;
//}
//
//
//class tcPlayApp : public QCoreApplication
//{
//public:
//    tcPlayApp ( int & argc, char ** argv);
//
//    KeyPressEater *m_keyPressEater;
//};
//
//bool myEveFilter(void *message, long *result)
//{
//    Q_UNUSED(message);
//    Q_UNUSED(result);
//    return true;
//}
//
//tcPlayApp::tcPlayApp ( int & argc, char ** argv)
//: QCoreApplication (argc, argv)
//{
//    Filter *fl = new Filter();
//    //m_keyPressEater = new KeyPressEater();
//    //installEventFilter(m_keyPressEater);
//    setEventFilter(myEveFilter);
//}
//
//
//
//
//#include "main.moc"
//int main(int argc, char *argv[])
//{
//    printf ("Hello World\n");
//
//    tcPlayApp a(argc, argv);
//
//    return a.exec();
//}
//
