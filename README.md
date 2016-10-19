# 2016_3rd_gameproject_prototype_moving

##캐릭터 이동과 에니메이션 프로토타입
1. 조이스틱이나 키보드로 조작한다.
2. 8방향 이동.
3. 움직임의 예:https://www.youtube.com/watch?v=fYDDm45SPxk (단 쿼터뷰는 무시 한다.)
4. 우선 키보드로 구현한후 자료를 다 읽어 본후 조이스틱을 시도해 보기로 함

##설명
##10월10일
###'KeyBoardLayer.h'/'KeyBoardLayer.cpp'
* 키보드 입력이벤트를 받아서 키보드에 어떤 키를 누르고 있는지('m_keyboardArrow') 어떤 키를 누르고 있는지를 기록합니다.
* 키보드의 방향값은 비트플래그를 이용해서 저장합니다.
* 기록한 방향값을 'KeyboardLayer::GetKeyboardInput()' 함수로 반환합니다.
* 'KeyboardLayer::update(float delta)' 함수로 게임의 메인루프에서 특정동작을 합니다.

###'UserClass.h'/'UserClass.cpp'
* 플레이어의 캐릭터클래스 입니다.
* 방향변수('m_currentDirection')와 애니메이션을 만들기 위한 맴버번수를 갖습니다.
* 각각의 방향을 나타내는 열거형 'enum direction'은 앞의 방향은 키보드 방향키를 뒤의 숫자는 캐릭터의 방향을 시계표시법으로 나타냅니다.
* 캐릭터의 기본방향은 초기화시에 0600시방향을 보도록 설정했습니다.
* 'SetDirection(const unsigned int &keyboardDirection)' 함수로 현재 캐릭터의 방향을 설정하고
* 'MoveUserClass(float dt)' 함수는 방향에 따라 애니메이션을 만들고, 움직임을 생성해 스프라이트에 추가 합니다.
* 아직 윗방향 까지 밖에 구현을 못했습니다. 아마 움직임을 만드는것을 함수로 뺄수 있을 것 같습니다.
* 그리고 스프라이트는 원래 그림파일을 잘라서 머리와 몸통을 각각 합치고 **TexturePacker**를 이용해 아틀라스 이미지로 만들어서 사용했습니다.

###추신
* 총 22시간 정도 걸린것같습니다.
* 그런데 그림파일을 자르고 붙이는데 한 12시간 정도 사용을 한것 같습니다.
* **TexturePacker**이용법을 찾고 아틀라스 이미지로 만드는데 한 3시간 정도 걸린것 같습니다.
* 키보드 입력부분과 캐릭터를 클래스를 나누는것을 고민하는데 5시간 정도 걸린것 같습니다.
* 나머지는 코드구현과 마지막에 애니메이션 만드는곳에서 디버깅 하는데 사용한것 같습니다.

##10월12일
###'KeyBoardLayer.h'/'KeyBoardLayer.cpp'
* 키보드 입력이벤트를 받아서 키보드에 어떤 키를 누르고 있는지('m_keyboardArrow') 어떤 키를 누르고 있는지를 기록합니다.
* 키보드의 방향값은 비트플래그를 이용해서 저장합니다.
* 기록한 방향값을 'KeyboardLayer::GetKeyboardInput()' 함수로 반환합니다.
* 'KeyboardLayer::update(float delta)' 함수로 게임의 메인루프에서 특정동작을 합니다.

###'UserClass.h'/'UserClass.cpp'
* 애니메이션을 만드는 곳과 좌표상의 움직임을 만드는 곳을 분리했습니다.(```UserClass::MakeAnimation()```)
* 애니메이션을 구성하는 각각의 스프라이트는 동일한이름에 끝의 숫자만 같습니다(moveSprite%d.png)
* 애니메이션 함수내에서는 각각의 방향을 나타내는 숫자(비트플래그)마다 for문을 돌려서 애니메이션을 만들어 주는데 하나의 애니메이션이 8개의 스프라이트를 가지므로 비트플레그에 10(const int SPRITE_FILE_NUMBER= 10;)을 곱한값부터 8을 더한값 이전까지 for문을 실행합니다.
* 또 입력이 계속되면 매번 애니메이션이 처음부터 시작되는 문제가 있어서 애니메이션을 무한히 돌려주고 방향이 바뀔때만 바꿔주는 방식으로 바꿨습니다.
* 그래서 이전 방향을 기록하는 멤버가 m_beforeDirection 입니다.'
* 잘못된 입력, 방향기 3개나 4개를 동시에 누르거나 반대 방향의 방향키 2개를 누른경우 애니메이션에 영향을 주지 않습니다.
* 기존에 있던 MoveBY를 이용한 이동은 애니메이션에 추가를 해줘야하고 정지를 시키려면 위의 애니메이션처럼 따로 정지를 시켜줘야 했기때문에 setPosition을 이용해서 구현했습니다. 그리고 이동방향을 정하기위한 단위벡터 unitVec[2] 가 추가 됐습니다.
* 속도를 의미하는 const int PIXEL_PER_SECOND멤버변수가 생겼습니다.


###추신
* 중간에 디버그 하는 부분이 있는데 이부분은 주변에서 알려 준거라서 공부가 필요 할것같습니다.
* 각각의 방향을 누르면 잘 작동하지만 방향키 3개를 누르다가 3개중 한개의 키에서 손을 때면 움직이지 않습니다. 두개 일때도 마찬가지입니다. 

##10월17
###'UserClass.h'/'UserClass.cpp'
* 자신이 몬스터인지 아닌지 설정하는 함수 추가
```
void UserClass::IAmMonster()
{
	amIMonster = 1;
}
```
* 에러입력을 setDirection 함수의 디폴트 부분에서 모두 NO_MOVE로 바꿔주어서 에러처리를 간략화
```
...

default:
	{
		m_currentDirection = NO_MOVE;
		m_unitVec[0] = 0;
		m_unitVec[1] = 0;
		break;
	}
	}
}
```
* 공격모션을 만들어내는 MakeActionAnimation() 함수 추가
* 새로만든 CharacterManage클래스에 공격정보를 보내는 GetActionInfo() 함수 정의(구현중 일단 애니메이션부터 먼저)
* 액션역시 비트연사자를 통해서 같은 변수에서 전달되기때문에 액션 비트와 움직임 비트를 추출하는 InterpretKeyboardInput(const unsigned int & keyboardDirection)함수 추가
###'KeyBoardLayer.h'/'KeyBoardLayer.cpp'
* 이전에 키를 때었을 때 움직임이 정지 하는 버그는 비트연산자'~'과 논리연산자 '!'를 착각해서 사용해서 생긴 문제였음 이부분을 수정함
```
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_keyboardInput &= ~(KEY_BOARD_INPUT::LEFT);
	}
```
###'CharacterManage.h/'CharacterManage.ccp'
* 새로만드는 클래스는 캐릭터의 공격범위를 받아서  그범위에 적이 있는지 확인해서 상호작용을 하게 해주려고 만든 클래스 인데 차라리 코코스의 물리엔진을 사용하는게 좋을것같다는 생각을 함 지금은 아직 애니메이션 구현중이기때문에 그냥 구현은 구체적이지 않음.
###추신
* 애니메이션을 구현했지만 좌우를 반대로 구현함.
* 또 공격 모션도중 계속 움직이는 현상이 존재함 애니메이션 을 시퀀스로 구현해서 종료 표시를 해주는 방법으로 해결할수 있지 않을까? 라고 생각해봄
##10월19
###'UserClass.h'/'UserClass.cpp'
