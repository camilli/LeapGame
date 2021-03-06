#include "../../include/SFMLKernel.hpp"

SFMLKernel::SFMLKernel(SampleListener *list, Controller *contro)
{
    _listener = list;
    _controller = contro;
    _window = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME, sf::Style::Fullscreen);
    _currentModule = new HomeController(_window, this, "Home");
    _music.openFromFile("res/music.wav");
    _music.setVolume(25);
    _music.setLoop(true);
    _music.play();
    cout << "-> SFML initialisation : Done." << endl;
}

void SFMLKernel::loadModule(IController::Module module)
{
    IController *tmp;

    tmp = _currentModule;
    switch (module)
    {
        case IController::Home:
            _currentModule = new HomeController(_window, this, "Home");
            break;

        case IController::Game:
            cout << "Changement vers game" << endl;
            _currentModule = new GameController(_window, this, "Game");
	    break;
        case IController::Results:
            cout << "Changement vers results" << endl;
	    
	    _currentModule = new ResultsController(_window, this, "Results", ((GameController *)_currentModule)->getPoint());
            break;
        case IController::Rank:
            cout << "Changement vers results" << endl;
            _currentModule = new RankController(_window, this, "Results");
        break;
    }
}

int SFMLKernel::loop()
{
    cout << "-> Loop started: " << endl;

    while (_window->isOpen())
    {
        Event event;

        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                _window->close();
            _currentModule->eventManager(event);
        }
        _window->clear();
        _currentModule->display();
        _window->display();
    }
}

SFMLKernel::~SFMLKernel()
{
}
