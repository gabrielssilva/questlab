<?php

    $features = array();
    $coordinates = array();

    // Add points
    foreach($stations as &$station)
    {
        if(!is_null($station['longitude']) && !is_null($station['latitude'])) {
            $coordinate = array(
                floatval($station['longitude']),
                floatval($station['latitude'])
            );
            $coordinates[] = $coordinate;
            // Marker
            $features[] = array(
                'type'          => 'Feature',
                'id'            => $station['id'],
                'geometry'      => array(
                    'type'          => 'Point',
                    'coordinates'   => $coordinate
                )
            );
            // Label
            $features[] = array(
                'type'          => 'Feature',
                'id'            => $station['id'].'-label',
                'properties'    => array(
                    'name'      => $station['title'],
                ),
                'geometry'      => array(
                    'type'          => 'Point',
                    'coordinates'   => $coordinate
                )
            );
        }
    }

    // Add lines between points
    if($hasgroup) {
        $features[] = array(
            'type'      => 'Feature',
            'name'      => 'Line',
            'geometry'  => array(
                'type'          => 'LineString',
                'coordinates'   => $coordinates
            )
        );
    }

?>
<?=json_encode(array(
    'type'      => 'FeatureCollection',
    'features'  => $features
))?>
