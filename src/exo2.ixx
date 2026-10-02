module;
import std;

export module exo2;

export namespace exo2 {
    class Vector {
    public:
        Vector(const double x, const double Y, const double Z) : x{x}, y{Y}, z{Z} {
            std::cout << "Vector(x,y,z) called" << std::endl;
        };

        Vector(const Vector& vector): x{vector.x}, y{vector.y}, z{vector.z} {
            std::cout << "Vector(const Vector&) copy called" << std::endl;
        }

        Vector(Vector&& vector) noexcept: x{vector.x}, y{vector.y}, z{vector.z} {
            vector.x = 0.0;
            vector.y = 0.0;
            vector.z = 0.0;
            std::cout << "Vector(Vector&&) move called" << std::endl;
        }

        Vector& operator=(const Vector& vector) {
            x = vector.x;
            y = vector.y;
            z = vector.z;
            std::cout << "operator=(const Vector&) copy called" << std::endl;
            return *this;
        }

        Vector& operator=(Vector&& vector) noexcept {
            x = vector.x;
            y = vector.y;
            z = vector.z;
            vector.x = 0.0;
            vector.y = 0.0;
            vector.z = 0.0;
            std::cout << "operator=(Vector&&) move called" << std::endl;
            return *this;
        }

        void Homothety(const double value) {
            x *= value;
            y *= value;
            z *= value;
        }

        void Sum1(const Vector vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;
        }

        void Sum2(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;
        }

        std::string ToString() const {
            return std::format("({0:.2f},{1:.2f},{2:.2f})", x, y, z);
        }

        double GetX() const { return x; }
        double GetY() const { return y; }
        double GetZ() const { return z; }

        void SetX(const double x) { this->x = x; }
        void SetY(const double y) { this->y = y; }
        void SetZ(const double z) { this->z = z; }

    private:
        double x;
        double y;
        double z;
    };

    class Application {
    public:
        Application() {
            auto v1 = Vector{12.34, 56.78, 90.12};
            std::cout << v1.ToString() << std::endl;
            v1.Homothety(2);
            std::cout << v1.ToString() << std::endl;
            const auto v2 = Vector{1.1, 2.2, 3.3};
            v1.Sum1(v2); // Clion devrait afficher une icône indiquant une copie d'objet
            std::cout << v1.ToString() << std::endl;
            v1.Sum2(v2);
            std::cout << v1.ToString() << std::endl;

            auto copy = v1;
            auto moved = std::move(copy);
            std::cout << "moved: " << moved.ToString() << std::endl;
            std::cout << "source after move: " << copy.ToString() << std::endl;
        }
    };
}
