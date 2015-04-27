<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>

<h1><i class="fa fa-map-marker fa-fw"></i><?=_('Map')?></h1>
<div id="map" class="map" style="background-image:url('<?=$linker->link(array('grafics','paper.jpg'))?>')"></div>
<script type="text/javascript">
    var extent = [0, 0, <?=$map['width']?>, <?=$map['height']?>];
    var projection = new ol.proj.Projection({
        code: 'pixel',
        units: 'pixels',
        extent: extent
    });
    var map;
    $(document).ready(function() {
        map = new ol.Map({
            target: 'map',
            layers: [
                new ol.layer.Image({
                    source: new ol.source.ImageStatic({
                        url: '<?=$linker->link(array('media','seminarymap',$seminary['url']))?>',
                        projection: projection,
                        imageExtent: extent
                    })
                })
            ],
            controls: ol.control.defaults().extend([
                new ol.control.OverviewMap({
                    collapsed: true,
                })
            ]),
            view: new ol.View({
                projection: projection,
                center: ol.extent.getCenter(extent),
                zoom: 1,
                extent: extent
            }),
        });
    });
</script>
