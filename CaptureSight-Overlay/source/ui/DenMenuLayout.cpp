#include <tesla.hpp>
#include <ui/DenMenuLayout.hpp>
#include <ui/RaidSearchLayout.hpp>

DenMenuLayout::DenMenuLayout(std::vector<std::shared_ptr<csight::Den>> dens, std::string title) {
  this->dens = dens;
  this->title = title;
}

tsl::Element* DenMenuLayout::createUI() {
  auto rootFrame = new tsl::element::Frame();
  auto denList = new tsl::element::List();
  auto titleBlock = new tsl::element::CustomDrawer(
      100, FB_WIDTH, 200, FB_WIDTH,
      std::bind(&DenMenuLayout::AddTitleBlock, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

  for (u32 i = 0; i < this->dens.size(); i++) {
    auto den = this->dens[i];
    auto title = "Id: " + std::to_string(den->GetDenId()) + " - Shiny " + std::to_string(den->GetShinyFrame());
    auto listItem = new tsl::element::ListItem(title);
    listItem->setClickListener(std::bind(&DenMenuLayout::OnClickDen, this, den, std::placeholders::_1));
    denList->addItem(listItem);
  }

  rootFrame->addElement(titleBlock);
  rootFrame->addElement(denList);

  return rootFrame;
}

void DenMenuLayout::AddTitleBlock(u16 x, u16 y, tsl::Screen* screen) {
  screen->drawString(this->title.c_str(), false, 20, 100, 20, tsl::a(0xFFFF));
}

bool DenMenuLayout::OnClickDen(std::shared_ptr<csight::Den> den, s64 keys) {
  if (keys == KEY_A) {
    // Do something when key A was pressed while this list item was focused
    this->changeTo(new RaidSearchLayout(den->GetSeed(), 5));

    // Return true for if this view handled the input
    return true;
  }

  return false;
}
