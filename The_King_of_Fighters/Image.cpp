#include "Image.h"

HRESULT Image::Init(int width, int height)
{
    HDC hdc = GetDC(g_hWnd);      // ������ ������ ���� ��������
    // �� ��Ʈ�� ����
    imageInfo = new IMAGE_INFO;
    imageInfo->width = width;
    imageInfo->height = height;
    imageInfo->loadType = ImageLoadType::Empty;
    imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // ���� ������ DC 
                                  // �⺻������ Bitmap�� ����Ǿ� �ִ�.
    imageInfo->hOldBit =
        (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

    reverseDc = CreateCompatibleDC(hdc);
    hBitmap1 = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(reverseDc, hBitmap1);

    ReleaseDC(g_hWnd, hdc);

    //if (SUCCEEDED(E_FAIL))
    //{

    //}

    if (imageInfo->hBitmap == NULL)   // ��Ʈ�� ������ �������� ��
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
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // ���� ������ DC 
                                  // �⺻������ Bitmap�� ����Ǿ� �ִ�.
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
    imageInfo->hMemDc = CreateCompatibleDC(hdc);   // ���� ������ DC 
                                  // �⺻������ Bitmap�� ����Ǿ� �ִ�.
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

    // �̹����� ��ü ������ �ҽ�
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
    BitBlt(hdc,            // ���� ������ DC
        0,            // ����� ��Ʈ���� ���� ��ġ x
        0,            // ����� ��Ʈ���� ���� ��ġ y
        imageInfo->width,   // ���� ������ ���� ũ��
        imageInfo->height,   // ���� ������ ���� ũ��
        imageInfo->hMemDc,   // ���� DC
        0,               // ���� ��Ʈ�� ���� ���� ��ġ x
        0,               // ���� ��Ʈ�� ���� ���� ��ġ y
        SRCCOPY);         // ���� �ɼ�
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
        BitBlt(hdc,            // ���� ������ DC
            destX - (imageInfo->width / 2),            // ����� ��Ʈ���� ���� ��ġ x
            destY - (imageInfo->height / 2),            // ����� ��Ʈ���� ���� ��ġ y
            imageInfo->width,   // ���� ������ ���� ũ��
            imageInfo->height,   // ���� ������ ���� ũ��
            imageInfo->hMemDc,   // ���� DC
            0,               // ���� ��Ʈ�� ���� ���� ��ġ x
            0,               // ���� ��Ʈ�� ���� ���� ��ġ y
            SRCCOPY);         // ���� �ɼ�
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
                (imageInfo->frameHeight),      // ��ü ������ ��

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
                (imageInfo->frameHeight),      // ��ü ������ ��

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
        BitBlt(hdc,            // ���� ������ DC
            destX - (imageInfo->width / 2),            // ����� ��Ʈ���� ���� ��ġ x
            destY - (imageInfo->height / 2),            // ����� ��Ʈ���� ���� ��ġ y
            imageInfo->width,   // ���� ������ ���� ũ��
            imageInfo->height,   // ���� ������ ���� ũ��
            imageInfo->hMemDc,   // ���� DC
            0,               // ���� ��Ʈ�� ���� ���� ��ġ x
            0,               // ���� ��Ʈ�� ���� ���� ��ġ y
            SRCCOPY);         // ���� �ɼ�
    }
}