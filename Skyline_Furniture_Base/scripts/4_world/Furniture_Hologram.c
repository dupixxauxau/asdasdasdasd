modded class Hologram
{	
	ItemBase FurnitureCollision()
	{
		vector center;
		vector relative_ofset;
		vector absolute_ofset = "0 0.01 0";
		vector orientation = GetProjectionOrientation();
		vector edge_length;
		vector min_max[2];
		ref array<Object> excluded_objects = new array<Object>;
		ref array<Object> collided_objects = new array<Object>;
		
		m_Projection.GetCollisionBox( min_max );
		relative_ofset[1] = ( min_max[1][1] - min_max[0][1] ) / 2.4;
		center = m_Projection.GetPosition() + relative_ofset + absolute_ofset;
		edge_length = GetCollisionBoxSize( min_max );
		excluded_objects.Insert( m_Projection );

		if ( GetGame().IsBoxColliding( center, orientation, edge_length, excluded_objects, collided_objects ) )
		{	
			for( int i = 0; i < collided_objects.Count(); i++ )
			{
				Object obj_collided = collided_objects[i];

				if( obj_collided.IsInherited(Skyline_Gun_Cabinet_Holo) )
				{
					return Skyline_Gun_Cabinet_Holo.Cast(obj_collided);
				}
				if( obj_collided.IsInherited(Skyline_Gun_Cabinet) )
				{
					return Skyline_Gun_Cabinet.Cast(obj_collided);
				}

				if( obj_collided.IsInherited(Skyline_Gun_Rack_Holo) )
				{
					return Skyline_Gun_Rack_Holo.Cast(obj_collided);
				}
				if( obj_collided.IsInherited(Skyline_Gun_Rack) )
				{
					return Skyline_Gun_Rack.Cast(obj_collided);
				}

				if( obj_collided.IsInherited(Skyline_Fridge_Holo) )
				{
					return Skyline_Fridge_Holo.Cast(obj_collided);
				}
				if( obj_collided.IsInherited(Skyline_Fridge) )
				{
					return Skyline_Fridge.Cast(obj_collided);
				}

				if( obj_collided.IsInherited(Skyline_Shelf_Holo) )
				{
					return Skyline_Shelf_Holo.Cast(obj_collided);
				}
				if( obj_collided.IsInherited(Skyline_Shelf) )
				{
					return Skyline_Shelf.Cast(obj_collided);
				}

				if( obj_collided.IsInherited(Skyline_StorageBox_Holo) )
				{
					return Skyline_StorageBox_Holo.Cast(obj_collided);
				}
				if( obj_collided.IsInherited(Skyline_StorageBox) )
				{
					return Skyline_StorageBox.Cast(obj_collided);
				}
			}
		}
		return null;
	}

	override string ProjectionBasedOnParent()
	{
		ItemBase item_in_hands = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());
		
		if (item_in_hands.IsInherited(Skyline_Kit_Gun_Cabinet))
			return "Skyline_Gun_Cabinet_Holo";

		if (item_in_hands.IsInherited(Skyline_Kit_Gun_Rack))
			return "Skyline_Gun_Rack_Holo";

		if (item_in_hands.IsInherited(Skyline_Kit_Fridge))
			return "Skyline_Fridge_Holo";

		if (item_in_hands.IsInherited(Skyline_Kit_Shelf))
			return "Skyline_Shelf_Holo";

		if (item_in_hands.IsInherited(Skyline_Kit_StorageBox))
			return "Skyline_StorageBox_Holo";

		return super.ProjectionBasedOnParent();
	}
	
    override EntityAI PlaceEntity( EntityAI entity_for_placing )
    {    
        ItemBase item_in_hands = ItemBase.Cast( m_Player.GetHumanInventory().GetEntityInHands() );
    
        if ( item_in_hands && item_in_hands.CanMakeGardenplot() )
        {
            Class.CastTo(entity_for_placing, GetGame().CreateObject( m_Projection.GetType(), m_Projection.GetPosition() ));
        }
            
        if( entity_for_placing.CanAffectPathgraph() )
        {        
            entity_for_placing.SetAffectPathgraph( true, false );
            
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, entity_for_placing);
        }
        
        return entity_for_placing;
    } 

    override void EvaluateCollision(ItemBase action_item = null)
    {
		ItemBase item_in_hands = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());
		
        if (item_in_hands && item_in_hands.IsInherited(Skyline_Kit_Gun_Cabinet))
        {
            SetIsColliding(false);
            return;
        }

        if (item_in_hands && item_in_hands.IsInherited(Skyline_Kit_Gun_Rack))
        {
            SetIsColliding(false);
            return;
        }

        if (item_in_hands && item_in_hands.IsInherited(Skyline_Kit_Fridge))
        {
            SetIsColliding(false);
            return;
        }

        if (item_in_hands && item_in_hands.IsInherited(Skyline_Kit_Shelf))
        {
            SetIsColliding(false);
            return;
        }

        if (item_in_hands && item_in_hands.IsInherited(Skyline_Kit_StorageBox))
        {
            SetIsColliding(false);
            return;
        }

        super.EvaluateCollision(action_item);
    }
}
