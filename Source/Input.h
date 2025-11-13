#pragma once


namespace Input {
	//キーボード取得関連
	// キーボードの状態を更新
	void KeyStateUpdate();
	// キーが離された瞬間
	bool IsKeyUP(int keyCode);
	// キーが押された瞬間（押下）
	bool IsKeyDown(int keyCode);
	// キーが押されている間
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown(); // マウスのボタンが押された瞬間
	bool IsMouseUP(); // マウスのボタン場が離された瞬間
	bool IsMouseKeep(); // マウスのボタンが押されている間
	bool IsButtonDown(int button);
	bool IsButtonUp(int button);
	bool IsButtonKeep(int button);
}

//MOUSE_INPUT_LEFT   => 0x0001
//MOUSE_INPUT_MIDDLE => 0x0004
//MOUSE_INPUT_RIGHT  => 0x0002