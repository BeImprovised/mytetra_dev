#ifndef __TREEKNOWMODEL_H__ // __TREENODE_H__
#define __TREEKNOWMODEL_H__ // __TREENODE_H__

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QtXml>

#include "TreeModel.h"

// KnowTreeModel - класс с удобными методами для управления данными дерева
// Внимание! Данный класс наследуется от класса TreeModel

class XmlTree;
class ClipboardBranch;
class TreeScreen;


class KnowModel : public TreeModel {
    Q_OBJECT

public:
    KnowModel(QObject *parent = 0); // KnowTreeModel(const QStringList &headers, QDomDocument domModel, QObject *parent = 0);
    KnowModel(boost::intrusive_ptr<TreeItem> _root_item, QObject *parent = 0);
    ~KnowModel();

    std::shared_ptr<XmlTree> init_from_xml(QString file_name);
    std::shared_ptr<XmlTree> init_from_xml(std::shared_ptr<XmlTree> xmlt);
    void reload(void);

    QDomElement dom_from_treeitem(boost::intrusive_ptr<TreeItem> root_item);

    void save(void);


    // Получение индекса подчиненного элемента с указанным номером
    QModelIndex index_direct(const QModelIndex &_parent_index, int n) const;

    //    QModelIndex index(boost::intrusive_ptr<TreeItem> item);
    boost::intrusive_ptr<TreeItem> item(QStringList path) const;
    boost::intrusive_ptr<TreeItem> item(const QModelIndex &_index) const;
    // Поиск ветки с указанным ID
    //    boost::intrusive_ptr<TreeItem> item(QString id) const;
    //    boost::intrusive_ptr<TreeItem> item_by_name(QString name) const;

    QModelIndexList indexes(std::function<bool(boost::intrusive_ptr<TreeItem>)> _equal);
    //    boost::intrusive_ptr<TreeItem> item_by_url(QUrl find_url)const;
    // Функция ищет ветку с указанным ID и возвращает ссылку не неё в виде TreeItem *
    // Если ветка с указанным ID не будет найдена, возвращается NULL
    //    template<typename url_type = url_full>
    // boost::intrusive_ptr<TreeItem> item_by_url(const QUrl &_find_url, equal_type _equal)const;
    boost::intrusive_ptr<TreeItem> item(std::function<bool(boost::intrusive_ptr<TreeItem>)> _equal)const;          //const QUrl &_find_url, equal_type _equal


    // Возвращает общее количество записей, хранимых в дереве
    int count_records_all(void) const;

    // Возвращает количество записей в ветке и всех подветках
    int size_of(boost::intrusive_ptr<TreeItem> it) const;



    void re_encrypt(QString previousPassword, QString currentPassword);

    bool is_contains_crypt_branches(void) const;

    QStringList record_path(QString recordId) const;

    //    // Проверка наличия идентификатора ветки во всем дереве
    //    bool is_item_exists(QString findId);

    // Проверка наличия идентификатора записи во всем дереве
    //    bool is_id_exists(QString findId) const;

#ifdef _with_record_table
    void record_to_item();
#endif

    void clear();


    //    bool is_global_root() {return _is_global_root;}
    void synchronized(bool _sysynchronized) {this->_synchronized = _sysynchronized;}
    bool synchronized() {return _synchronized;}
    boost::intrusive_ptr<TreeItem> duplicated_remove(boost::intrusive_ptr<TreeItem> target, boost::intrusive_ptr<TreeItem> source);
    void record_remove(boost::intrusive_ptr<TreeItem> _item);




private:


    void init(QDomDocument *dom_model);

    //    // Функция заполнения дерева из DOM-документа
    //    void setup_modeldata(QDomDocument *dommodel, boost::intrusive_ptr<TreeItem> self);

    // Преобразование DOM в Item модель. Функция рекурсивного обхода элементов DOM-документа
    void dom_to_records(QDomElement _record_dom_element, boost::intrusive_ptr<TreeItem> self);

    // Преобразование Item в DOM модель
    void dom_from_treeitem(std::shared_ptr<QDomDocument> doc, QDomElement &xml_data, boost::intrusive_ptr<TreeItem> curr_item);

    // Перемещение ветки вверх или вниз
    QModelIndex model_move_up_dn(const QModelIndex &_index
                                 , int(TreeItem::*_move)()   //int direction
                                );

    //    int get_all_record_count_recurse(boost::intrusive_ptr<TreeItem> item, int mode);

    //    QString paste_sub_branch_recurse(boost::intrusive_ptr<TreeItem> item, QString startBranchId, ClipboardBranch *subbranch);

    //    boost::intrusive_ptr<TreeItem> item_by_id_recurse(boost::intrusive_ptr<TreeItem> item, QString id, int mode);

    //    bool is_contains_crypt_branches_recurse(boost::intrusive_ptr<TreeItem> item, int mode);

    // Добавление подветки из буфера обмена относительно указанного элемента
    QString model_paste_child_impl(boost::intrusive_ptr<TreeItem> _target_item, int _sibling_order, ClipboardBranch *subbranch);

    //    QStringList record_path_recurse(boost::intrusive_ptr<TreeItem> item, QStringList currentPath, QString recordId, int mode);

    //    bool is_item_id_exists_recurse(boost::intrusive_ptr<TreeItem> item, QString findId, int mode);

    //    bool is_record_id_exists_recurse(boost::intrusive_ptr<TreeItem> item, QString findId, int mode);

    bool format_check(QDomElement elementFormat);

    bool update_sub_version_from_1_to_2(void);

    // Добавление новой ветки после указанной ветки
    boost::intrusive_ptr<TreeItem> model_add_sibling(const QModelIndex &_index, QString id, QString name);
    boost::intrusive_ptr<TreeItem> model_move_sibling(const QModelIndex &_index, boost::intrusive_ptr<TreeItem> _source_item);

    // Добавление новой подветки к указанной ветке
    boost::intrusive_ptr<TreeItem> model_add_child_new(const QModelIndex &_index, QString id, QString name);
    boost::intrusive_ptr<TreeItem> model_move_child(const QModelIndex &_index, boost::intrusive_ptr<TreeItem> it);

    // Добавление новой подветки к Item элементу
    boost::intrusive_ptr<TreeItem> model_add_child_new(boost::intrusive_ptr<TreeItem> parent, int pos, QString id, QString name);

#ifdef _with_record_table
    boost::intrusive_ptr<TreeItem> lock_child_add(boost::intrusive_ptr<Record> record, boost::intrusive_ptr<TreeItem> parent);
#endif

    boost::intrusive_ptr<TreeItem> model_move_child(boost::intrusive_ptr<TreeItem> parent, int pos, boost::intrusive_ptr<TreeItem> _source_item, int _mode = ADD_NEW_RECORD_AFTER);
    //    boost::intrusive_ptr<TreeItem> add_new_branch(boost::intrusive_ptr<TreeItem> parent, boost::intrusive_ptr<TreeItem> item);

    // Перемещение ветки вверх и вниз
    //    QModelIndex branch_move_up(const QModelIndex &_index);
    //    QModelIndex branch_move_dn(const QModelIndex &_index);

    QString model_paste_child(const QModelIndex &_index, ClipboardBranch *subbranch);
    QString model_paste_sibling(const QModelIndex &_index, ClipboardBranch *subbranch);

    boost::intrusive_ptr<TreeItem> intercept_self(boost::intrusive_ptr<TreeItem> _item);
    boost::intrusive_ptr<TreeItem> synchronize(boost::intrusive_ptr<TreeItem> source);

private:

    // QModelIndex get_item_index_recurse(QModelIndex currindex, TreeItem *finditem, int mode);
    QString _xml_file_name = "";

    bool _synchronized = false;

    //    bool _is_global_root = false;
    friend class TreeScreen;

};






#endif // __TREEKNOWMODEL_H__   // __TREENODE_H__