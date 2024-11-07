module;
import std;

export module exo6;

export namespace exo6 {

    class VectorUtils {
    public:
        // Affiche le contenu d'un vecteur d'entiers
        static void Print(const std::vector<int>& vec) {
            std::for_each(vec.begin(), vec.end(),
                [](const int& n) { std::cout << n << ' '; });
            std::cout << std::endl;
        }

        // Tri un vecteur d'entiers et supprimer les doublons
        static void SortAndRemoveDuplicates(std::vector<int>& vec) {
            std::sort(vec.begin(), vec.end());
            vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        }

        // Renvoi le nombre d'entiers supérieur à la valeur `threshold`
        static int CountGreatersThan(const std::vector<int>& vec, int threshold) {
            // count_if renvoie un iterator_traits on doit donc le transtyper en int
            return static_cast<int>(std::count_if(vec.begin(), vec.end(),
                    [threshold](const int x) { return x > threshold; }));
        }
    };

    class Application {
    public:
        Application() {
            auto vec = std::vector<int>{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};
            VectorUtils::Print(vec);
            VectorUtils::SortAndRemoveDuplicates(vec);
            VectorUtils::Print(vec);
            constexpr auto threshold = 5;
            std::cout
                << "Numbers greater than " << threshold
                << ": " << VectorUtils::CountGreatersThan(vec, threshold)
                << std::endl;
        }
    };
}
