#ifndef CPUINFOMODEL_H
#define CPUINFOMODEL_H

#include <QAbstractListModel>
#include "cpuinfobase.h"
#include <QQuickItem>


/// @class qmlCpuInfoItem
/// @brief CpuInfoItem for the qml-presentation of a row in the qml list model
/// the item allows the programmer to decide which informations in the rows of the model will be shown
/// the information also can be manipulated here
class qmlCpuInfoItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(myNamespace::CPUINFOTYPE type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)

public:
    qmlCpuInfoItem(QObject* parent=0);
    myNamespace::CPUINFOTYPE type() const;
    QColor textColor() const;

public slots:
    void setType(myNamespace::CPUINFOTYPE type);
    void setTextColor(QColor textColor);

signals:
    void typeChanged(myNamespace::CPUINFOTYPE type);
    void textColorChanged(QColor textColor);

private:
    myNamespace::CPUINFOTYPE m_type;
    QColor m_textColor;
};

/// @class cpuInfoModel
/// @brief List-Model for the presentation of the cpu data for each processor
/// the data for the model has to be set with the property cpuInfo
/// the internal list of qmlCpuInfoItems decides which rows will be shown
/// @example
///
/// MyCpuInfoModel {
///     id: infoModel
///     cpuInfo: _myCpuInfo
///     MyCpuInfoModelItem {
///         type: MyNamespace.PROCESSOR
///     }
///     MyCpuInfoModelItem {
///         type: MyNamespace.VENDOR_ID
///     }
///     MyCpuInfoModelItem {
///         type: MyNamespace.CPU_FAMILY
///     }
///     MyCpuInfoModelItem {
///         type: MyNamespace.MODEL
///     }

class cpuInfoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(cpuInfoBase* cpuInfo READ cpuInfo WRITE setCpuInfo)

public:
    /// @enum CpuInfoModelRoles
    /// @brief Information supported by the model for the QmlListView
    enum CpuInfoModelRoles {
        ValueRole = Qt::UserRole + 1,
        ColorRole,
        TranslatedText
    };
    cpuInfoModel(QObject* parent);
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    cpuInfoBase* cpuInfo() const;
    void addInfoItem(qmlCpuInfoItem* item);
    virtual QHash<int,QByteArray> roleNames() const;
    short processorId() const;
    void setProcessorId(short processorId);

public slots:
    void setCpuInfo(cpuInfoBase* cpuInfo);

signals:

private:
    QList<qmlCpuInfoItem*> m_qmlCpuInfoItems;
    cpuInfoBase* m_cpuInfo;
    int m_count;
    short m_processorId;
};



/// @class qmlCpuInfoModelContainer
/// @brief QML-Representation of the CpuInfoModel
/// Is a Qml-Container-Class which contains the qmlCpuInfoItem as Qml-Childs
/// the qmlCpuInfoItem presents a row in the tableview
/// the class also contains the real 'TableModel' in the QProperty 'model' and
/// the model will be filled with qmlCpuInfoItems
class qmlCpuInfoModelContainer : public QQuickItem
{
    Q_PROPERTY(QObject* cpuInfo READ cpuInfo WRITE setCpuInfo)
    Q_PROPERTY(QObject* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(short processorId READ processorId WRITE setProcessorId)
    Q_OBJECT

public:
    qmlCpuInfoModelContainer(QQuickItem *parent = 0);
    QObject* cpuInfo() const;
    QObject* model() const;
    virtual void componentComplete();
    short processorId() const;

public slots:
    void setCpuInfo(QObject *cpuInfo);
    void setModel(QObject* model);
    void setProcessorId(short arg);

signals:
    void cpuInfoChanged(QObject* cpuInfo);
    void modelChanged(QObject* model);
    void cpuCoreIdChanged(short arg);

private:
    QObject* m_model;
    void readChilds();
};

#endif // CPUINFOMODEL_H
