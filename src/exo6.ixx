module;
import std;

export module exo6;

export namespace exo6 {

    class VectorUtils {
    public:
        // std::span fournit une vue non propriétaire sur une séquence contiguë.
        static void Print(const std::span<const int> values, const std::string_view label = {}) {
            if (!label.empty()) {
                std::cout << label << ": ";
            }
            std::ranges::for_each(values, [](const int n) { std::cout << n << ' '; });
            std::cout << std::endl;
        }

        // Tri un vecteur d'entiers et supprimer les doublons
        static void SortAndRemoveDuplicates(std::vector<int>& vec) {
            std::ranges::sort(vec);
            const auto duplicates = std::ranges::unique(vec);
            vec.erase(duplicates.begin(), duplicates.end());
        }

        static int CountGreaterThan(const std::span<const int> values, const int threshold) {
            return static_cast<int>(std::ranges::count_if(values,
                [threshold](const int value) { return value > threshold; }));
        }

        // Renvoi le nombre d'entiers supérieur à la valeur `threshold` (Une view est évaluée paresseusement et ne copie pas les éléments).
        static auto GreaterThan(const std::span<const int> values, const int threshold) {
            return values | std::views::filter(
                [threshold](const int value) { return value > threshold; });
        }
    };

    class Application {
    public:
        Application() {
            auto vec = std::vector<int>{1, 4, 5, 2, 1, 7, 8, 5, 8, 2, 9};
            VectorUtils::Print(vec, "before");
            VectorUtils::SortAndRemoveDuplicates(vec);
            VectorUtils::Print(vec, "after");

            constexpr auto threshold = 5;
            std::cout << "Numbers greater than " << threshold << ": "
                      << VectorUtils::CountGreaterThan(vec, threshold) << std::endl;

            std::cout << "Filtered: ";
            for (const auto value : VectorUtils::GreaterThan(vec, threshold)) {
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }
    };
}
