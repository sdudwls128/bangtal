#include <bangtal>
using namespace bangtal;

int main()
{
	auto room1 = Scene::create("룸1", "Images/배경-1.png");
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", room1, 800, 270);
	auto closed1 = true;
	auto key = Object::create("Images/열쇠.png", room1, 600, 150);
	key->setScale(0.2f);
	key->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		object->pick();
		return true;
		});
	
	auto room2 = Scene::create("룸2", "Images/배경-2.png");
	auto door2 = Object::create("Images/문-왼쪽-닫힘.png", room2, 200, 245);
	auto closed2 = true;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", room2, 940, 263);
	auto closed3 = true;
	auto plant = Object::create("Images/화분.png", room2, 940, 263);
	door3->hide();
	door1->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		if (closed1) {
			if (key->isHanded()) {
				object->setImage("Images/문-오른쪽-열림.png");
				closed1 = false;
			}
			else {
				showMessage("열쇠가 필요해~~~");
			}
		}
		else {
			room2->Scene::enter();
			plant->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
				object->locate(room2, 800, 260);
				door3->show();
				return true;
				});

			door2->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
				showMessage("이 문은 이미 탈출한 방으로 통하는 문이구나!\n숨겨진 다른 문을 찾아보자!");
				return true;
				});
			door3->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
				if (closed3) {
					object->setImage("Images/문-오른쪽-열림.png");
					closed3 = false;
					showMessage("야호~ 탈출 성공!");
				}
				else {
					endGame();
				}
				return true;
			});
		}
		return true;
		});

	startGame(room1);
}