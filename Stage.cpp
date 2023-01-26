#include"Stage.h"
#include"Resources.h"

Stage::Stage() {

	 blockSize = 128;//ブロックサイズ

	//スクロール処理
	 scrollStartX = 400;
	 lineY = 0;

	 scrollX = 0;

	 monitorX = 0;

	 resources = new Resources;
	

}




void Stage::Draw() {

	
	//ブロックの描画
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 30; x++) {
			if (map[y][x] == 1) {
				Novice::DrawSprite(
					x * 128 - scrollX, y * 128, resources->gh1, 1, 1, 0.0f, WHITE);
			}
			if (map[y][x] == 2) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->gh1, 1, 1, 0.0f, RED);
			}
			if (map[y][x] == 3) {
				monitorX = x * 128 - scrollX;
				Novice::DrawSprite(
					monitorX, y * 128, resources->gh1, 1, 1, 0.0f, BLUE);
			}
		}
	}


}

