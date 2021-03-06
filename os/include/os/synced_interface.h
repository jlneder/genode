/*
 * \brief  Utility for synchronizing the access of interface functions
 * \author Norman Feske
 * \date   2013-05-16
 *
 * The 'Synced_interface' utility makes the serialization of interface
 * function calls easy. The 'Synced_interface' is a functor that takes a lock
 * and a pointer to an interface as arguments. When called, the functor
 * returns a smart pointer to the interface. When this smart pointer gets
 * dereferenced, the smart pointer takes care of acquiring and releasing
 * the lock while the interface function is executed.
 */

#ifndef _INCLUDE__OS__SYNCED_INTERFACE_H_
#define _INCLUDE__OS__SYNCED_INTERFACE_H_

/* Genode includes */
#include <base/lock.h>

namespace Genode {

	template <typename IF, typename LOCK = Genode::Lock>
	class Synced_interface
	{
		public:

			class Guard
			{
				private:

					LOCK &_lock;
					IF   *_interface;

					Guard(LOCK &lock, IF *interface)
					: _lock(lock), _interface(interface)
					{
						_lock.lock();
					}

					friend class Synced_interface;

				public:

					~Guard() { _lock.unlock(); }

					IF *operator -> () { return _interface; }
			};

		private:

			LOCK &_lock;
			IF   *_interface;

		public:

			Synced_interface(LOCK &lock, IF *interface)
			: _lock(lock), _interface(interface) { }

			Guard operator () ()
			{
				return Guard(_lock, _interface);
			}
	};
}

#endif /* _INCLUDE__OS__SYNCED_INTERFACE_H_ */
