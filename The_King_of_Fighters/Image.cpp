#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);      // 권한이 굉장히 많은 총지배인
    // 빈 비트맵 생성
    imageInfo = new IMAGE_INFO;
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = ImageLoadType::Empty;
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // 새로 생성된 DC 
                                  // 기본적으로 Bitmap에 연결되어 있다.
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

    reverseDc = CreateCompatibleDC(hdc);
    hBitmap1 = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(reverseDc, hBitmap1);

    ReleaseDC(g_hWnd, hdc);

    //if (SUCCEEDED(E_FAIL))
    //{

    //}

    if (imageInfo->hBitmap == NULL)   // 비트맵 생성에 실패했을 때
    {
        Release();
        return E_FAIL;
    }

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO;
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = ImageLoadType::File;
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // 새로 생성된 DC 
                                  // 기본적으로 Bitmap에 연결되어 있다.
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);


    reverseDc = CreateCompatibleDC(hdc);
    hBitmap1 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    SelectObject(reverseDc, hBitmap1);


    ReleaseDC(g_hWnd, hdc);

    this->isTransparent = isTrans;
    this->transColor = transColor;

    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    HDC hdc = GetDC(g_hWnd);

    imageInfo = new IMAGE_INFO;
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = ImageLoadType::File;
    imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
        LR_LOADFROMFILE);
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // 새로 생성된 DC 
                                  // 기본적으로 Bitmap에 연결되어 있다.
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

    reverseDc = CreateCompatibleDC(hdc);
    hBitmap1 = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    SelectObject(reverseDc, hBitmap1);

    ReleaseDC(g_hWnd, hdc);

    this->isTransparent = isTrans;
    this->transColor = transColor;

    imageInfo->maxFrameX = maxFrameX;
    imageInfo->maxFrameY = maxFrameY;
    imageInfo->currFrameX = 0;
    imageInfo->currFrameY = 0;
    imageInfo->frameWidth = width / maxFrameX;
    imageInfo->frameHeight = height / maxFrameY;


    if (imageInfo->hBitmap == NULL)
    {
        Release();
        return E_FAIL;
    }

    // 이미지를 전체 뒤집는 소스
    /*StretchBlt(
        imageInfo->hMemDc,
        0,
        0,
        imageInfo->width,
        imageInfo->height,
        imageInfo->hMemDc,
        imageInfo->width,
        0,
        -imageInfo->width,
        imageInfo->height,
        SRCCOPY);*/

    return S_OK;

}

void Image::Release()
{
    if (imageInfo)
    {
        SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
        DeleteObject(imageInfo->hBitmap);
        DeleteDC(imageInfo->hMemDc);

        delete imageInfo;
        imageInfo = nullptr;
    }

    DeleteObject(hBitmap1);
    DeleteDC(reverseDc);
}

void Image::Render(HDC hdc)
{
    BitBlt(hdc,            // 복사 목적지 DC
        0,            // 복사될 비트맵의 시작 위치 x
        0,            // 복사될 비트맵의 시작 위치 y
        imageInfo->width,   // 원본 복사할 가로 크기
        imageInfo->height,   // 원본 복사할 세로 크기
        imageInfo->hMemDc,   // 원본 DC
        0,               // 원본 비트맵 복사 시작 위치 x
        0,               // 원본 비트맵 복사 시작 위치 y
        SRCCOPY);         // 복사 옵션
}

void Image::Render(HDC hdc, int destX, int destY)
{
    if (isTransparent)
    {
        GdiTransparentBlt(
            hdc,
            destX - (imageInfo->width / 2),
            destY - (imageInfo->height / 2),
            imageInfo->width,
            imageInfo->height,
            imageInfo->hMemDc,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        BitBlt(hdc,            // 복사 목적지 DC
            destX - (imageInfo->width / 2),            // 복사될 비트맵의 시작 위치 x
            destY - (imageInfo->height / 2),            // 복사될 비트맵의 시작 위치 y
            imageInfo->width,   // 원본 복사할 가로 크기
            imageInfo->height,   // 원본 복사할 세로 크기
            imageInfo->hMemDc,   // 원본 DC
            0,               // 원본 비트맵 복사 시작 위치 x
            0,               // 원본 비트맵 복사 시작 위치 y
            SRCCOPY);         // 복사 옵션
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, ePlayer player)
{
    if (isTransparent)
    {
        if (player == ePlayer::player1)
        {
            StretchBlt(
                reverseDc,
                imageInfo->frameWidth * frameX,
                imageInfo->frameHeight * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                imageInfo->hMemDc,
                imageInfo->frameWidth * (frameX + 1),
                imageInfo->frameHeight * frameY,
                -imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY);

            GdiTransparentBlt(
                hdc,
                destX - (imageInfo->frameWidth / 2),
                destY - (imageInfo->frameHeight / 2),
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),      // 전체 프레임 수

                reverseDc,
                (imageInfo->frameWidth) * frameX,
                (imageInfo->frameHeight) * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                transColor
            );
        }
        else
        {
            GdiTransparentBlt(
                hdc,
                destX - (imageInfo->frameWidth / 2),
                destY - (imageInfo->frameHeight / 2),
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),      // 전체 프레임 수

                imageInfo->hMemDc,
                (imageInfo->frameWidth) * frameX,
                (imageInfo->frameHeight) * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                transColor
            );
        }
    }
    else
    {
        BitBlt(hdc,            // 복사 목적지 DC
            destX - (imageInfo->width / 2),            // 복사될 비트맵의 시작 위치 x
            destY - (imageInfo->height / 2),            // 복사될 비트맵의 시작 위치 y
            imageInfo->width,   // 원본 복사할 가로 크기
            imageInfo->height,   // 원본 복사할 세로 크기
            imageInfo->hMemDc,   // 원본 DC
            0,               // 원본 비트맵 복사 시작 위치 x
            0,               // 원본 비트맵 복사 시작 위치 y
            SRCCOPY);         // 복사 옵션
    }
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, bool scene)
{
    if (isTransparent)
    {
        if (scene)
        {
            StretchBlt(
                reverseDc,
                imageInfo->frameWidth * frameX,
                imageInfo->frameHeight * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                imageInfo->hMemDc,
                imageInfo->frameWidth * frameX,
                imageInfo->frameHeight * frameY,
                imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY);

            GdiTransparentBlt(
                hdc,
                0,
                0,
                WIN_SIZE_X,
                WIN_SIZE_Y,      // 전체 프레임 수

                reverseDc,
                (imageInfo->frameWidth) * frameX,
                (imageInfo->frameHeight) * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                transColor
            );
        }
        else
        {
            GdiTransparentBlt(
                hdc,
                destX - (imageInfo->frameWidth / 2),
                destY - (imageInfo->frameHeight / 2),
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),      // 전체 프레임 수

                imageInfo->hMemDc,
                (imageInfo->frameWidth) * frameX,
                (imageInfo->frameHeight) * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                transColor
            );
        }
    }
    else
    {
        BitBlt(hdc,            // 복사 목적지 DC
            destX - (imageInfo->width / 2),            // 복사될 비트맵의 시작 위치 x
            destY - (imageInfo->height / 2),            // 복사될 비트맵의 시작 위치 y
            imageInfo->width,   // 원본 복사할 가로 크기
            imageInfo->height,   // 원본 복사할 세로 크기
            imageInfo->hMemDc,   // 원본 DC
            0,               // 원본 비트맵 복사 시작 위치 x
            0,               // 원본 비트맵 복사 시작 위치 y
            SRCCOPY);         // 복사 옵션
    }
}



void Image::KingRender(HDC hdc, int destX, int destY, int frameX, int frameY, ePlayer player)
{
    if (isTransparent)
    {
        if (player == ePlayer::player1)
        {
            StretchBlt(
                reverseDc,
                imageInfo->frameWidth * frameX,
                imageInfo->frameHeight * frameY,
                (imageInfo->frameWidth),
                (imageInfo->frameHeight),
                imageInfo->hMemDc,
                imageInfo->frameWidth * (frameX + 1),
                imageInfo->frameHeight * frameY,
                -imageInfo->frameWidth,
                imageInfo->frameHeight,
                SRCCOPY);

            GdiTransparentBlt(
                hdc,
                destX - 235,
                destY - 313,
                imageInfo->frameWidth, imageInfo->frameHeight,	// 전체 프레임 수 를 각각 저장해보자

                reverseDc,
                imageInfo->frameWidth * frameX,
                imageInfo->frameHeight * frameY,
                imageInfo->frameWidth, imageInfo->frameHeight,
                transColor
            );
        }
        else
        {
			GdiTransparentBlt(
				hdc,
				destX - 235,
				destY - 313,
				imageInfo->frameWidth, imageInfo->frameHeight,	// 전체 프레임 수 를 각각 저장해보자

				imageInfo->hMemDc,
				imageInfo->frameWidth * frameX,
				imageInfo->frameHeight * frameY,
				imageInfo->frameWidth, imageInfo->frameHeight,
				transColor
			);
        }
        
    }
}

void Image::HpRender(HDC hdc, int destX, int destY, float hpCalculate, int damage,  ePlayer player)
{

    if (isTransparent)
    {
        if (player == ePlayer::player1)
        {
            GdiTransparentBlt(
                hdc,
                destX - imageInfo->width / 2 + hpCalculate * damage,
                destY - imageInfo->height / 2,
                imageInfo->width - hpCalculate * damage,
                imageInfo->height,

                imageInfo->hMemDc,
                0 + hpCalculate * damage, 0,
                imageInfo->width - hpCalculate * damage, imageInfo->height,
                transColor
            );
        }
        else
        {
			GdiTransparentBlt(
				hdc,
				destX - imageInfo->width / 2 ,
				destY - imageInfo->height / 2,
				imageInfo->width - hpCalculate * damage,
				imageInfo->height,

				imageInfo->hMemDc,
				0 , 0,
				imageInfo->width - hpCalculate * damage, imageInfo->height,
				transColor
			);
        }
        
    }

}

void Image::BattleRender(HDC hdc, int destX, int destY)
{
    if (isTransparent)
    {
        /* StretchBlt(
             reverseDc,
             0 ,
             0 ,
             imageInfo->width,
             imageInfo->height,

             imageInfo->hMemDc,
             0,
             0,
             (imageInfo->width),
             imageInfo->height,
             SRCCOPY);*/

        GdiTransparentBlt(
            hdc,
            destX - imageInfo->width / 2,
            destY - imageInfo->height / 2,
            imageInfo->width,
            imageInfo->height,

            reverseDc,
            0, 0,
            imageInfo->width, imageInfo->height,
            transColor
        );
    }
    else
    {
        BitBlt(hdc,            // 복사 목적지 DC
            destX,            // 복사될 비트맵의 시작 위치 x
            destY,            // 복사될 비트맵의 시작 위치 y
            imageInfo->width,   // 원본 복사할 가로 크기
            imageInfo->height,   // 원본 복사할 세로 크기
            imageInfo->hMemDc,   // 원본 DC
            0,               // 원본 비트맵 복사 시작 위치 x
            0,               // 원본 비트맵 복사 시작 위치 y
            SRCCOPY);         // 복사 옵션
    }
}