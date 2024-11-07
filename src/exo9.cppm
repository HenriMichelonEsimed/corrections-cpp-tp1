module;
import std;

export module exo9;

export namespace exo9 {

    template<typename T>
    struct Node {
        T data;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    template<typename T>
    class BinaryTree {
    public:
        void Insert(const T value) {
            if (root == nullptr) {
                root = std::make_unique<Node<T>>(value);
            } else {
                RecursiveInsert(root, value);
            }
            size += 1;
        }

        // La fonction lamba appelée à chaque noeud renvoi un bool pour stopper
        // le parcours, si besoin
        bool Traversal(const std::function< bool(T&) >& lambda) const {
            return RecursiveTraversal(root, lambda);
        }

        // Vide l'arbre
        void Clear() {
            root = nullptr;
            size = 0;
        }

        // Renvoie `true` si `value` est présente dans l'arbre
        // Nécessite une surcharge de l'opérateur `==` pour T
        bool Contains(const T value) const {
            bool found{false};
            Traversal([&](T& v) {
                if (value == v) {
                    found = true;
                    return true;
                }
                return false;
            });
            return found;
        }

        // Retourne le nombre de noeuds de l'arbre
        std::uint64_t GetSize() const { return size; }

    private:
        std::unique_ptr<Node<T>> root{nullptr};
        std::uint64_t size{0};

        void RecursiveInsert(std::unique_ptr<Node<T>>& node, T value) {
            if (node == nullptr) {
                node = std::make_unique<Node<T>>(value);
            } else if (value < node->data) {
                RecursiveInsert(node->left, value);
                // std::cout << "l";
            } else {
                RecursiveInsert(node->right, value);
                // std::cout << "r";
            }
        }

        bool RecursiveTraversal(const std::unique_ptr<Node<T>>& node, const std::function< bool(T&) >& lambda) const {
            if (node != nullptr) {
                if (RecursiveTraversal(node->left, lambda)) return true;
                if (lambda(node->data)) return true;
                if (RecursiveTraversal(node->right, lambda)) return true;
            }
            return false;
        }
    };

    // Entrée d'un dictionnaire clé K/valeur V
    // et opérateurs associés pour les insertion et recherches dans l'arbre
    template<typename K, typename V>
    struct MapEntry {
        K key;
        V value;

        friend bool operator<(const MapEntry& lhs, const MapEntry& rhs) {
            return lhs.key < rhs.key;
        }

        friend bool operator<=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(rhs < lhs);
        }

        friend bool operator>(const MapEntry& lhs, const MapEntry& rhs) {
            return rhs < lhs;
        }

        friend bool operator>=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(lhs < rhs);
        }

        friend bool operator==(const MapEntry& lhs, const MapEntry& rhs) {
            return lhs.key == rhs.key;
        }

        friend bool operator!=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(lhs == rhs);
        }
    };

    // Dictionnaire clé K/valeur V basé sur un arbre binaire
    template<typename K, typename V>
    class Map {
    public:
        // Vide le dictionnaire
        void Clear() { tree.Clear(); }

        // Renvoie le nombre d'éléments dans le dictionnaire
        std::uint64_t GetSize() const { return tree.GetSize(); }

        // Renvoie `true` si il existe une entrée ayant la clé `key`
        bool Contains(const K& key) const {
            return tree.Contains({key});
        }

        // Renvoie la valeur associée à la clé `key`
        V& Get(const K& key) {
            if (!tree.Contains({key})) {
                throw std::out_of_range("Key not found");
            }
            MapEntry<K, V> *result;
            tree.Traversal([&](MapEntry<K, V>& entry) {
                if (entry.key == key) {
                    result = &entry;
                    return true;
                }
                return false;
            });
            return result->value;
        }

        // Créé ou modifier la valeur associées à la clé `key`
        void Put(const K& key, const V& value) {
            if (!tree.Contains({key})) {
                tree.Insert({key, value});
                return;
            }
            auto f = [&](MapEntry<K, V>& entry) {
                if (entry.key == key) {
                    entry.value = value;
                    return true;
                }
                return false;
            };
            tree.Traversal(f);
        }
    private:
        BinaryTree<MapEntry<K, V>> tree;
    };


    class Application {
        public:
            Application() {
                BinaryTree<std::string> tree;

                tree.Insert("C++");
                tree.Insert("ASM");
                tree.Insert("GO");
                tree.Insert("Rust");
                tree.Insert("JavaScript");

                std::cout << "In order traversal: ";
                tree.Traversal([](const std::string& i) {
                    std::cout << i << ' ';
                    return false;
                });
                std::cout << "\n";

                std::cout << "Tree Size : " << tree.GetSize() << "\n";
                std::cout << "Tree Contains(\"Rust\") : " << tree.Contains("Rust") << "\n";
                std::cout << "Tree Contains(\"C#\") : " << tree.Contains("C#") << "\n";

                Map<std::string, std::int64_t> map;
                map.Put("Jean", 18);
                map.Put("Georges", 20);
                std::cout << "Map Size : " << map.GetSize() << "\n";
                std::cout << "Map Contains(\"Jean\") : " << map.Contains("Jean") << "\n";
                std::cout << "Map Contains(\"Jeanne\") : " << map.Contains("Jean") << "\n";
                std::cout << "Jean : " << map.Get("Jean") << "\n";
                map.Put("Jean", 8);
                std::cout << "Jean : " << map.Get("Jean") << "\n";
            }
    };

}