#include <iostream>

#include "bud/inc.h"

using namespace std;
using namespace bud;


Window *window;
Texture *texture;

class TestMaster : public Master {
public:
    using Master::Master;
    virtual void onQuit() override {
        kill();
    }
    Random *rand = nullptr;
    virtual void update() override {
        if (!rand) rand = new Random();
        if (this->countChildNode() < 200) {
            Sprite *sprite = new Sprite(texture);
            sprite->selfDelete(true);
            sprite->clip = sprite->texture()->rect() / Vector2D<int>(5, 3);
            sprite->pos.x = rand->next(0, window->width() - sprite->clip.w);
            sprite->pos.y = rand->next(0, window->height() - sprite->clip.h);
            Motion *motion = new AnimationMotion(ANIMATION_LAYOUT::H, 12, 2, rand->next(3, 5));
            motion->selfDelete(true);
            motion->finishKill(true);
            sprite->motion.run(motion);

            this->addNode(sprite);
        }
    }
};

int main() {
    BUD _init;

    Node n1;
    int *a = n1.alloc<int>();
    *a = 10;
    int *b = n1.allocated_data<int>();
    cout << *b << endl;

    window = new Window("BUD Test", 640, 480);
    texture = new Texture(window->getRenderer(), "/opt/RTP/Graphics/Animations/Fire2.png");

    TestMaster master(window->getRenderer());
    master.showFPS(true);

    Tile *tile = new Tile(texture);
    tile->selfDelete();

    master.addNode(tile);

    LocalNode *node = new LocalNode();
    node->selfDelete(true);

    int time = 0;
    node->whenUpdate([&time]() {
        //if (Input::toggle(KEY::K)) cout << "toggle K" << endl;
        //if (Input::trigger(KEY::K)) cout << "trigger K" << endl;
        //if (Input::press(KEY::K)) cout << "press K" << endl;
        //if (Input::repeat(KEY::K)) cout << "repeat K" << endl;
        //if (Input::release(KEY::K)) cout << "release K: " << Input::release(KEY::K) << endl;

        //if (Input::trigger(vector<KEY>({KEY::J, KEY::K, KEY::L }))) cout << "trigger J, K, L" << endl;
        //if (Input::press(vector<KEY>({KEY::J, KEY::K, KEY::L }))) cout << "press J, K, L" << endl;
        //if (Input::repeat(vector<KEY>({KEY::J, KEY::K, KEY::L }))) cout << "repeat J, K, L" << endl;
        //if (Input::combo(vector<KEY>({KEY::J, KEY::K, KEY::L }))) cout << "comboEx J, K, L: " << time++ << endl;
        //if (Input::combo(vector<KEY>({KEY::J, KEY::K, KEY::K, KEY::J }))) cout << "comboEx J, K, K, J: " << time++ << endl;
        //if (Input::combo({KEY::J, KEY::K, KEY::K, KEY::J})) cout << "combo J, K, K, J: " << time++ << endl;
        //if (Input::click(KEY::K, 3)) cout << "triple click K: " << time++ << endl;

        //if (Input::toggle(MOUSE::LEFT)) cout << "toggle mouse left" << endl;
        //if (Input::trigger(MOUSE::LEFT)) cout << "trigger mouse left" << endl;
        //if (Input::press(MOUSE::LEFT)) cout << "press mouse left" << endl;
        //if (Input::repeat(MOUSE::LEFT)) cout << "repeat mouse left" << endl;
        //if (Input::release(MOUSE::LEFT)) cout << "release mouse left: " << Input::release(MOUSE::LEFT) << endl;
        //if (Input::click(MOUSE::LEFT, 2)) cout << "double click mouse left" << endl;
        //if (Input::comboEx({MOUSE::LEFT, MOUSE::LEFT, KEY::J, KEY::K})) cout << "combo LB, LB, J, K: " << time++ << endl;

    });

    for (int i = 0; i < 100; ++i) {
        cout << bud::random.u() << endl;
    }

    master.addNode(node);

    master.loop();

    return 0;
}