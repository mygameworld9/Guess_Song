// trie.cpp
#include "trie.h"

Trie::Trie() {
    root = std::make_shared<TrieNode>();
}

// 插入一个单词到字典树
void Trie::insert(const QString& word) {
    std::shared_ptr<TrieNode> current = root;
    for (const QChar& ch : word) {
        if (!current->children.contains(ch)) {
            current->children[ch] = std::make_shared<TrieNode>();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
}

// 基于前缀给出建议
QVector<QString> Trie::suggest(const QString& prefix) {
    QVector<QString> suggestions;
    std::shared_ptr<TrieNode> current = root;

    // 导航到前缀的末尾节点
    for (const QChar& ch : prefix) {
        if (!current->children.contains(ch)) {
            return suggestions; // 如果前缀不存在，返回空列表
        }
        current = current->children[ch];
    }

    // 从前缀末尾节点开始，查找所有可能的单词
    findWords(current, prefix, suggestions);
    return suggestions;
}

// 递归函数，用于查找所有以当前节点为起点的单词
void Trie::findWords(std::shared_ptr<TrieNode> node, const QString& currentPrefix, QVector<QString>& suggestions) {
    if (node->isEndOfWord) {
        suggestions.append(currentPrefix);
    }

    // 对子节点进行排序，让建议列表有序
    QMapIterator<QChar, std::shared_ptr<TrieNode>> i(node->children);
    while (i.hasNext()) {
        i.next();
        findWords(i.value(), currentPrefix + i.key(), suggestions);
    }
}
