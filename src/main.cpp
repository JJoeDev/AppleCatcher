#include "../E2DE/E2DE.h"
#include <iostream>

unsigned int SetRandomPosX() {
    return rand() % 800;
}

int main(){
    e2e::Engine app("Simple game", 800, 800, SHOWN);

    app.SetAssetPath(app.GetPath().parent_path() / "textures"); // ./../build/bin/testures

    std::cout << app.GetAssetPath() << '\n';

    auto* eventHandler = app.GetEventInstance();

    eventHandler->NewMap("Horizontal");
    eventHandler->BindKey("Horizontal", e2e::KEYS::KEY_D, 1.0f);
    eventHandler->BindKey("Horizontal", e2e::KEYS::KEY_A, -1.0f);

#pragma region Apple initialization

    auto apple = app.GetScene().CreateEntity();
    apple.AddComponent<e2e::SpriteRendererComponent>(e2e::Color(255, 255, 255, 0)); // White box around entity
    apple.AddComponent<e2e::AABBCollisionBox>(1, e2e::Vector(50, 50));

    auto& appleT = apple.GetComponent<e2e::TransformComponent>();
    auto& appleRendr = apple.GetComponent<e2e::SpriteRendererComponent>();
    auto& appleColli = apple.GetComponent<e2e::AABBCollisionBox>();

    appleT.Position = e2e::Vector(400, 50);
    appleT.Scale = e2e::Vector(50, 50);
    app.LoadTexture(appleRendr, app.GetAssetPath() + "/Apple.png");

#pragma endregion
#pragma region Player initialization

    auto player = app.GetScene().CreateEntity();
    player.AddComponent<e2e::SpriteRendererComponent>(e2e::Color(0, 255, 0, 0)); // Green box around entity
    player.AddComponent<e2e::AABBCollisionBox>(1, e2e::Vector(50, 50));

    auto& plrT = player.GetComponent<e2e::TransformComponent>();
    auto& plrRendr = player.GetComponent<e2e::SpriteRendererComponent>();
    auto& plrColli = player.GetComponent<e2e::AABBCollisionBox>();

    plrT.Position = e2e::Vector(400, 700);
    plrT.Scale = e2e::Vector(50, 50);
    app.LoadTexture(plrRendr, app.GetAssetPath() + "/Basket.png");

#pragma endregion

    app.Update(); // Call before main loop to reset and initialize Delta Time

    e2e::Vector dir;

    unsigned int score = 0;

    float appleSpeed{0.3f};

    bool playing{true};

    while(!app.Terminate() && playing){
        app.Update();
        app.Render();

        dir.x = eventHandler->GetValue("Horizontal");

        plrT.Position += dir * 0.5f * app.GetDeltaTime();

        appleT.Position.y += appleSpeed * app.GetDeltaTime();
        appleT.Rotation += 0.1f * app.GetDeltaTime();

        if(appleColli.didCollide) {
            appleColli.didCollide = false;
            ++score;
            std::cout << "SCORE: " << score << '\n';
            appleT.Position.y = -100;
            appleT.Position.x = SetRandomPosX();
            appleSpeed += 0.05f;
        }

        if (appleT.Position.y > 800){
            appleT.Position = e2e::Vector(SetRandomPosX(), -100);
            playing = false;
        } 
    }

    std::cout << "GAME OVER | SCORE: " << score << std::endl;
    return 0;
}