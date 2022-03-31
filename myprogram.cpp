#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class WindowScreen {
private:
    int x, y;
    int width;
    int height;
public:
    void SetX(int& inputX) {
        x = inputX;
    }
    int GetX() {
        return x;
    }

    void SetY(int& inputY) {
        y = inputY;
    }
    int GetY() {
        return y;
    }

    void SetWidth(int& inputWidth) {
        width = inputWidth;
    }
    int GetWidth() {
        return width;
    }
    
    void SetHeight(int& inputHeight) {
        height = inputHeight;
    }
    int GetHeight() {
        return height;
    }
};

class MonitorScreen
{
private:
    char screenMonitor[50][80];
    WindowScreen window;
public:
    WindowScreen GetWindow() {
        return window;
    }
    void SetWindow(WindowScreen& inputWindow) {
        window = inputWindow;
    }
    
    void SetScreenMonitor(int x, int y, int line, int column, char pixel) {
        for (int i = x; i < line; i++) {
            for (int j = y; j < column; j++) {
                screenMonitor[i][j] = pixel;
            }
        }
    }
    void GetScreenMonitor() {
        for (int x = 0; x < 50; x++) {
            for (int y = 0; y < 80; y++) {
                std::cout << screenMonitor[x][y];
            }
            std::cout << '\n';
        }
    }

    void WindowInitialization() {
        std::srand(std::time(nullptr));
        
        int tempY = std::rand() % 80 + 1;
        window.SetY(tempY);
        
        int tempX = std::rand() % 50 + 1;
        window.SetX(tempX);

        int widthTemp = 80 - window.GetY();//
        int heightTemp = 50 - window.GetX();
        
        int tempWidth = std::rand() % widthTemp + 1 + window.GetY();
        window.SetWidth(tempWidth);

        int tempHeight = std::rand() % heightTemp + 1 + window.GetX();
        window.SetHeight(tempHeight);

        SetScreenMonitor(window.GetX(), window.GetY(), window.GetHeight(), window.GetWidth(), '1');
    }
};

bool CorrectInput(std::string& widthHeight) {
    bool good = true;
    if (widthHeight.length() == 2) {
        for (int i = 0; i < widthHeight.length() && good; i++) {
            if (widthHeight[i] < '0' || widthHeight[i] > '9')
                good = false;
        }
    } else if (widthHeight.length() == 1) {
        if (widthHeight[0] < '0' || widthHeight[0] > '9')
                good = false;
    } else good = false;
    return good;
}

class Teams {
friend bool CorrectInput(std::string& widthHeight);
public:
    void Resize(MonitorScreen& monitor) {
        std::cout << "Window width = " << monitor.GetWindow().GetWidth() - monitor.GetWindow().GetY() << ", Window height = " << monitor.GetWindow().GetHeight() - monitor.GetWindow().GetX() << '\n';
        int width, height; 
        do {
            std::cout << "Enter new window size(width(> 0 and <= " << 80 - monitor.GetWindow().GetY() << "), height(> 0 and <= " << 50 - monitor.GetWindow().GetX() << "))\n";
            
            std::string widthStr;
            do {
                std::cout << "width:";
                std::cin >> widthStr;
                if (CorrectInput(widthStr)) width = stoi(widthStr);
                else std::cout << "Wrong width value..\n"; 
            } while (!CorrectInput(widthStr));
            
            std::string heightStr;
            do {
                std::cout << "height:";
                std::cin >> heightStr;
                if (CorrectInput(heightStr)) height = stoi(heightStr);
                else std::cout << "Incorrect height value..\n"; 
            } while (!CorrectInput(heightStr));

            if (width <= 0 || width > 80 - monitor.GetWindow().GetY() || height <= 0 || height > 50 - monitor.GetWindow().GetX())
                std::cout << "Wrong, try again..\n";

        } while (width <= 0 || width > 80 - monitor.GetWindow().GetY() || height <= 0 || height > 50 - monitor.GetWindow().GetX());

        WindowScreen* windowTemp = new WindowScreen;
        int x = monitor.GetWindow().GetX();
        int y = monitor.GetWindow().GetY();
        windowTemp->SetY(y); 
        windowTemp->SetX(x);
        
        width += windowTemp->GetY(); 
        height += windowTemp->GetX();
        windowTemp->SetWidth(width);
        windowTemp->SetHeight(height);
        
        monitor.SetWindow(*windowTemp);
        delete windowTemp; windowTemp = nullptr;
        
        width = monitor.GetWindow().GetWidth();
        height = monitor.GetWindow().GetHeight();

        monitor.SetScreenMonitor(0, 0, 50, 80, '0');
        monitor.SetScreenMonitor(x, y, height, width, '1');

        std::cout << "New window size:\n";
        std::cout << "Window Width = " << monitor.GetWindow().GetWidth() - monitor.GetWindow().GetY() << ", Window height = " << monitor.GetWindow().GetHeight() - monitor.GetWindow().GetX() << '\n';
    }

    void Move(MonitorScreen& monitor) {
        std::cout << "Window X = " << monitor.GetWindow().GetY() << ", Window Y = " << monitor.GetWindow().GetX() << '\n';
        
        int width = monitor.GetWindow().GetWidth() - monitor.GetWindow().GetY();
        int height = monitor.GetWindow().GetHeight() - monitor.GetWindow().GetX();

        int x, y;
        do {
            std::cout << "Input Window Offset Vector(x(>= 0 and <= " << monitor.GetWindow().GetY() + (80 - monitor.GetWindow().GetY() - width) << "), y(>= 0 and <= " << monitor.GetWindow().GetX() + 
                    (50 - monitor.GetWindow().GetX() - height) << "))\n";
            
            std::string yStr;
            do {
                std::cout << "x:";
                std::cin >> yStr;
                if (CorrectInput(yStr)) y = stoi(yStr);
                else std::cout << "Incorrect \'x\'..\n"; 
            } while (!CorrectInput(yStr));
            
            std::string xStr;
            do {
                std::cout << "y:";
                std::cin >> xStr;
                if (CorrectInput(xStr)) x = stoi(xStr);
                else std::cout << "Incorrect \'y\'..\n"; 
            } while (!CorrectInput(xStr));

            if (y < 0 || y > monitor.GetWindow().GetY() + (80 - monitor.GetWindow().GetY() - width) || x < 0 || x > monitor.GetWindow().GetX() + (50 - monitor.GetWindow().GetX() - height))
                std::cout << "Wrong, try again..\n";
        } while (y < 0 || y > monitor.GetWindow().GetY() + (80 - monitor.GetWindow().GetY() - width) || x < 0 || x > monitor.GetWindow().GetX() + (50 - monitor.GetWindow().GetX() - height));

        WindowScreen* windowTemp = new WindowScreen;
        width += y;
        height += x;
        
        windowTemp->SetWidth(width); 
        windowTemp->SetHeight(height);
        windowTemp->SetY(y);
        windowTemp->SetX(x);

        monitor.SetWindow(*windowTemp);
        delete windowTemp; windowTemp = nullptr;

        x = monitor.GetWindow().GetX();
        y = monitor.GetWindow().GetY();
        width = monitor.GetWindow().GetWidth();
        height = monitor.GetWindow().GetHeight();

        monitor.SetScreenMonitor(0, 0, 50, 80, '0');
        monitor.SetScreenMonitor(x, y, height, width, '1');

        std::cout << "New Window Offset Vector:\n";
        std::cout << "Window X = " << monitor.GetWindow().GetY() << ", Window Y = " << monitor.GetWindow().GetX() << '\n';
    }

    void Display(MonitorScreen& monitor) {
        monitor.GetScreenMonitor();
    }
};

int main () { 
    MonitorScreen* monitor = new MonitorScreen;
    monitor->SetScreenMonitor(0, 0, 50, 80, '0');
    monitor->WindowInitialization();

    Teams* command = new Teams();
    
    std::string* strCommand = new std::string("");
    while (*strCommand != "close") {
        std::cout << "Choose command(move/resize/display/close): ";
        std::cin >> *strCommand;
        if (*strCommand == "move")          command->Move(*monitor);
        else if (*strCommand == "resize")   command->Resize(*monitor);
        else if (*strCommand == "display")  command->Display(*monitor);
        else if (*strCommand == "close")    continue;
        else                                std::cout << "Invalid command, please try again.\n";
    }
    delete strCommand; strCommand = nullptr;
    delete command; command = nullptr;
    delete monitor; monitor = nullptr;
}