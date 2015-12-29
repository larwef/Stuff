package queue

type Order struct {
	OrderFloor int
	OrderType int //order type. 1: internal order. 2: external order.
	OrderDir int //direction. Is 0 for internal orders. For external orders: 1 = Down, 2 = Up.
}