/*
 * 问题:
 * 找到链表的倒数第m个节点
 */

/*
 * 方法1
 * 首先遍历链表,统计链表的长度N
 * 然后再次遍历链表,找到第N-m个节点,即为倒数第m个节点
 *
 * 方法2
 * 使用两个指针，并使它们指向的节点相距m-1个
 * 然后同时向前移动两个指针,当一个指针指最后一个节点时,第二个指针指向倒数第m个节点
 */
