#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//³õÊ¼»¯Á´±í
	list.account_head = (Account *)malloc(sizeof(Account));
	list.program_head = (Program *)malloc(sizeof(Program));
	list.studio_head = (Studio *)malloc(sizeof(Studio));
	list.plan_head = (Plan *)malloc(sizeof(Plan));
	list.seat_head = (Seat *)malloc(sizeof(Seat));
	list.ticket_head = (Ticket *)malloc(sizeof(Ticket));
	list.record_head = (Record *)malloc(sizeof(Record));
	list.account_head->next = list.account_head->pre = NULL;
	list.program_head->next = list.program_head->pre =  NULL;
	list.studio_head->next =list.studio_head->pre = NULL;
	list.plan_head->next = list.plan_head->pre = NULL;
	list.seat_head->next = list.seat_head->pre = NULL;
	list.ticket_head->next = list.ticket_head->pre = NULL;
	list.record_head->next = list.record_head->pre = NULL;
	list.account_tail = list.account_head;
	list.program_tail = list.program_head;
	list.studio_tail = list.studio_head;
	list.plan_tail = list.plan_head;
	list.seat_head = list.seat_head;
	list.ticket_head = list.ticket_head;
	list.record_head = list.record_head;
}

