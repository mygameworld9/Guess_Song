// trie.h
#ifndef TRIE_H
#define TRIE_H

#include <QString>
#include <QVector>
#include <memory>
#include <QMap>

// 字典树节点
struct TrieNode {
    QMap<QChar, std::shared_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// 字典树类
class Trie {
public:
    Trie();
    void insert(const QString& word);
    QVector<QString> suggest(const QString& prefix);

private:
    std::shared_ptr<TrieNode> root;
    void findWords(std::shared_ptr<TrieNode> node, const QString& currentPrefix, QVector<QString>& suggestions);
};

#endif // TRIE_H
