#ifndef USINGFILES_H
#define USINGFILES_H

#include <QObject>
#include <vector>
#include <string>
class UsingFiles : public QObject
{
    Q_OBJECT
  public:
    explicit UsingFiles(QObject *parent = 0);
    
signals:
    
public slots:
    void setZaznaczPliki(std::vector<std::string> nazwy)
    {
        _zaznaczonePliki=nazwy;
    }
    void setSkopiowanePliki(std::vector<std::string> nazwy)
    {
        _skopiowanePliki=nazwy;
    }
    void setSkopiowanePliki(std::string nazwa)
    {
        _aktywnyKatalog=nazwa;
    }
private:
    std::vector<std::string> _zaznaczonePliki;
    std::vector<std::string> _skopiowanePliki;
    std::string _aktywnyKatalog;
};

#endif // USINGFILES_H
