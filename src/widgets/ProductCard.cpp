//
// Created by e.kravchenkova on 07.04.2025.
//
#include "ProductCard.h"

void ProductCard::deleteItemSlot() {
    if (!info.undef){
        emit deleteItem(info);
    }
}

void ProductCard::modifyItemSlot() {
    if (!info.undef){
        emit modifyItem(info);
    }
}
