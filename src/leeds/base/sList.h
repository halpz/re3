#pragma once

namespace base
{

template<typename T>
class cSList
{
public:
	struct tSItem
	{
		tSItem* next;
		T item;
	};
	// extra field on PS2
	tSItem* first;

	cSList() { first = nil; }
	void Insert(tSItem* item) { tSItem* n = first; first = item; item->next = n; }
	void Remove(tSItem* item) {
		if (first == item) {
			first = item->next;
			return;
		}
		tSItem* i = first;
		while (i && i->next != item)
			i = i->next;
		assert(i);
		i->next = item->next;

	}

};

}