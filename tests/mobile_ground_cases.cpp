int main() {
    GJGroundLayer ground;
    cocos2d::CCSprite g1Tile, g2Container, g2Tile, line;
    cocos2d::CCNode nested, unrelated;
    ground.m_ground1Sprite = &g1Tile;
    ground.m_ground2Sprite = &g2Container;
    ground.m_lineSprite = &line;
    g1Tile.parent = &ground;
    g2Container.parent = &ground;
    nested.parent = &g2Container;
    g2Tile.parent = &nested;
    line.parent = &ground;

    assert(GroundOwnership::owner(&g1Tile) == &ground);
    assert(GroundOwnership::owner(&g2Tile) == &ground);
    assert(GroundOwnership::part(&ground, &g1Tile) == GroundOwnership::Part::Ground1);
    assert(GroundOwnership::part(&ground, &g2Tile) == GroundOwnership::Part::Ground2);
    assert(GroundOwnership::part(&ground, &line) == GroundOwnership::Part::Line);
    assert(GroundOwnership::part(&ground, &unrelated) == GroundOwnership::Part::Other);
    assert(GroundOwnership::owner(&unrelated) == nullptr);
    std::cout << "PASS: floor sprite ancestry is classified for diagnostics only; stock ground remains authoritative\n";
}
