#pragma once
namespace Reverie
{
	class System
	{
	public:
		virtual ~System() = default;
		virtual void Initialize(Eventbus* eventbus) = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;

	};

	class SystemRegistry
	{
	public:
		SystemRegistry();
		~SystemRegistry();

        template<typename TSystem, typename... TArgs>
        TSystem* Register(TArgs&&... args)
        {
            auto system = std::make_unique<TSystem>(std::forward<TArgs>(args)...);
            TSystem* ptr = system.get();
            m_SystemList.push_back(ptr);
            m_SystemTable[typeid(TSystem)] = std::move(system);
            return ptr;
        }

        template<typename TSystem>
        TSystem* Get()
        {
            auto it = m_SystemTable.find(typeid(TSystem));
            if (it == m_SystemTable.end())
                return nullptr;
            return static_cast<TSystem*>(it->second.get());
        }

        void InitAll(Eventbus* eventbus)
        {
            for (auto system : m_SystemList)
                system->Initialize(eventbus);
        }

        void UpdateAll(float dt)
        {
            for (auto system : m_SystemList)
                system->OnUpdate();
        }

        void ShutdownAll()
        {
            for (auto system : m_SystemList)
                system->Shutdown();
            m_SystemList.clear();
            m_SystemTable.clear();
        }

	private:
		std::unordered_map<std::type_index, std::unique_ptr<System>> m_SystemTable;
        std::vector<System*> m_SystemList;
	};
}