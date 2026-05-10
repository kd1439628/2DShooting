#pragma once

class BaseObject;
class UI;

class Hit
{
public:

	// 全オブジェクトのリストを受け取り、当たり判定を一括実行する
	void AllCollision(std::vector<std::shared_ptr<BaseObject>>& objList);


	// UIと連携できるようにセットする関数
	void SetUI(std::shared_ptr<UI> ui) { m_ui = ui; }
	// 合計スコアを外から取得できるようにする
	int GetScore() const { return m_totalScore; }

private:
	// 個別の判定ロジック
	void CheckCollision(std::shared_ptr<BaseObject> objA, std::shared_ptr<BaseObject> objB, std::vector<std::shared_ptr<BaseObject>>& objList);

	std::shared_ptr<UI> m_ui = nullptr;
	int m_totalScore = 0;
};