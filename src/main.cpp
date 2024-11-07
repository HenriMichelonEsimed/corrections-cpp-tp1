import std;
import exo1;
import exo2;
import exo3;
import exo4;
import exo5;
import exo6;
import exo7;
import exo8;
import exo9;
import lzw;

int main(int argc, char **argv) {
    // exo1::Application app;
    // exo9::Application app;
    if (argc != 4) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    lzw::Application app(argv[1], argv[2], argv[3]);
    return 0;
}