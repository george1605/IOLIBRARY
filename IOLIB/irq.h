#pragma once
// irqs in user space
namespace io
{
#ifdef __linux__
	void __attribute__((interrupt)) int_handler() {}
#endif

#ifdef __ARM__
#define dis_isr __swi(0xFE)
#define enb_isr __swi(0xFF)
#endif
	class irq
	{
	private:
		int intr;
	public:
		irq(int x)
		{
			intr = x;
		}
	};
}