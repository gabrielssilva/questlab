<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('achievements','index',$seminary['url']))?>"><?=_('Achievements')?></a></li>
</ul>

<h1><?=_('Edit Achievement conditions')?></h1>
<form method="post">
    <fieldset>
        <legend><?=_('Conditions')?></legend>
        <ul>
            <?php foreach($conditions as &$condition) : ?>
            <li>
                <?php if($achievement['condition'] == 'date') : ?>
                    <label for="condition-<?=$condition['id']?>-select"><?=_('Date')?>:</label>
                    <input id="condition-<?=$condition['id']?>-select" type="text" name="conditions[<?=$condition['id']?>][select]" placeholder="SELECT" value="<?=$condition['select']?>" />
                <?php elseif($achievement['condition'] == 'character') : ?>
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Field')?>:</label>
                    <select id="condition-<?=$condition['id']?>-field" name="conditions[<?=$condition['id']?>][field]">
                        <?php foreach($characterFields as &$field) : ?>
                        <option value="<?=$field?>" <?php if($condition['field'] == $field) : ?>selected="selected"<?php endif ?>><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Value')?>:</label>
                    <input id="condition-<?=$condition['id']?>-value" type="text" name="conditions[<?=$condition['id']?>][value]" placeholder="<?=_('Value')?>" value="<?=$condition['value']?>" />
                <?php elseif($achievement['condition'] == 'quest') : ?>
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Field')?>:</label>
                    <select id="condition-<?=$condition['id']?>-field" name="conditions[<?=$condition['id']?>][field]">
                        <?php foreach($questFields as &$field) : ?>
                        <option value="<?=$field?>" <?php if($condition['field'] == $field) : ?>selected="selected"<?php endif ?>><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <input id="condition-<?=$condition['id']?>-count" type="checkbox" name="conditions[<?=$condition['id']?>][count]" <?php if($condition['count']) : ?>checked="checked"<?php endif ?> />
                    <label for="condition-<?=$condition['id']?>-count"><?=_('Count')?></label><br />
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Value')?>:</label>
                    <input id="condition-<?=$condition['id']?>-value" type="text" name="conditions[<?=$condition['id']?>][value]" placeholder="<?=_('Value')?>" value="<?=$condition['value']?>" /><br />
                    <label for="condition-<?=$condition['id']?>-quest"><?=_('Quest')?>:</label>
                    <select id="condition-<?=$condition['id']?>-quest" name="conditions[<?=$condition['id']?>][quest]">
                        <option value="" <?php if(is_null($condition['quest_id'])) : ?>selected="selected"<?php endif ?>><?=_('unset')?><option>
                        <?php foreach($quests as &$quest) : ?>
                        <option value="<?=$quest['url']?>" <?php if($condition['quest_id'] == $quest['id']) : ?>selected="selected"<?php endif ?>><?=$quest['title']?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-<?=$condition['id']?>-status"><?=_('Status')?>:</label>
                    <select id="condition-<?=$condition['id']?>-status" name="conditions[<?=$condition['id']?>][status]">
                        <option value="" <?php if(is_null($condition['status'])) : ?>selected="selected"<?php endif ?>><?=_('unset')?></option>
                        <option value="0" <?php if(!is_null($condition['status']) && $condition['status'] == 0) : ?>selected="selected"<?php endif ?>><?=_('entered')?></option>
                        <option value="1" <?php if($condition['status'] == 1) : ?>selected="selected"<?php endif ?>><?=_('submitted')?></option>
                        <option value="2" <?php if($condition['status'] == 2) : ?>selected="selected"<?php endif ?>><?=_('unsolved')?></option>
                        <option value="3" <?php if($condition['status'] == 3) : ?>selected="selected"<?php endif ?>><?=_('solved')?></option>
                    </select><br />
                    <label for="condition-<?=$condition['id']?>-groupby"><?=_('Group by')?>:</label>
                    <input id="condition-<?=$condition['id']?>-groupby" type="text" name="conditions[<?=$condition['id']?>][groupby]" placeholder="<?=_('Group by')?>" value="<?=$condition['groupby']?>" />
                <?php elseif($achievement['condition'] == 'achievement') : ?>
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Field')?>:</label>
                    <select id="condition-<?=$condition['id']?>-field" name="conditions[<?=$condition['id']?>][field]">
                        <?php foreach($achievementFields as &$field) : ?>
                        <option value="<?=$field?>" <?php if($condition['field'] == $field) : ?>selected="selected"<?php endif ?>><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <input id="condition-<?=$condition['id']?>-count" type="checkbox" name="conditions[<?=$condition['id']?>][count]" <?php if($condition['count']) : ?>checked="checked"<?php endif ?> />
                    <label for="condition-<?=$condition['id']?>-count"><?=_('Count')?></label><br />
                    <label for="condition-<?=$condition['id']?>-value"><?=_('Value')?>:</label>
                    <input id="condition-<?=$condition['id']?>-value" type="text" name="conditions[<?=$condition['id']?>][value]" placeholder="<?=_('Value')?>" value="<?=$condition['value']?>" /><br />
                    <label for="condition-<?=$condition['id']?>-achievement"><?=_('Achievement')?>:</label>
                    <select id="condition-<?=$condition['id']?>-achievement" name="conditions[<?=$condition['id']?>][achievement]">
                        <option value="" <?php if(is_null($condition['meta_achievement_id'])) : ?>selected="selected"<?php endif ?>><?=_('unset')?><option>
                        <?php foreach($achievements as &$a) : ?>
                        <option value="<?=$a['url']?>" <?php if($condition['meta_achievement_id'] == $a['id']) : ?>selected="selected"<?php endif ?>><?=$a['title']?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-<?=$condition['id']?>-groupby"><?=_('Group by')?>:</label>
                    <input id="condition-<?=$condition['id']?>-groupby" type="text" name="conditions[<?=$condition['id']?>][groupby]" placeholder="<?=_('Group by')?>" value="<?=$condition['groupby']?>" />
                <?php endif ?>
                <br />
                <input id="delete-<?=$condition['id']?>" type="checkbox" name="deletes[<?=$condition['id']?>]" <?php if(array_key_exists($condition['id'], $deletes)) : ?>checked="checked"<?php endif ?> />
                <label for="delete-<?=$condition['id']?>"><?=_('delete')?></label>
            </li>
            <?php endforeach ?>
            <li>
                <?php if($achievement['condition'] == 'date') : ?>
                    <label for="condition-new-select"><?=_('Date')?>:</label>
                    <input id="condition-new-select" type="text" name="conditions[new][select]" placeholder="<?=_('New condition')?>" value="" />
                <?php elseif($achievement['condition'] == 'character') : ?>
                    <label for="condition-new-field"><?=_('Field')?>:</label>
                    <select id="condition-new-field" name="conditions[new][field]">
                        <?php foreach($characterFields as &$field) : ?>
                        <option value="<?=$field?>"><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-new-value"><?=_('Value')?>:</label>
                    <input id="condition-new-value" type="text" name="conditions[new][value]" placeholder="<?=_('New condition')?>" value="" />
                <?php elseif($achievement['condition'] == 'quest') : ?>
                    <label for="condition-new-field"><?=_('Field')?>:</label>
                    <select id="condition-new-field" name="conditions[new][field]">
                        <?php foreach($questFields as &$field) : ?>
                        <option value="<?=$field?>"><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <input id="condition-new-count" type="checkbox" name="conditions[new][count]" />
                    <label for="condition-new-count"><?=_('Count')?></label><br />
                    <label for="condition-value"><?=_('Value')?>:</label>
                    <input id="condition-new-value" type="number" name="conditions[new][value]" placeholder="<?=_('Value')?>" value="" /><br />
                    <label for="condition-new-quest"><?=_('Quest')?>:</label>
                    <select id="condition-new-quest" name="conditions[new][quest]">
                        <option value=""><?=_('unset')?><option>
                        <?php foreach($quests as &$quest) : ?>
                        <option value="<?=$quest['url']?>"><?=$quest['title']?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-new-status"><?=_('Status')?>:</label>
                    <select id="condition-new-status" name="conditions[new][status]">
                        <option value=""><?=_('unset')?></option>
                        <option value="0"><?=_('entered')?></option>
                        <option value="1"><?=_('submitted')?></option>
                        <option value="2"><?=_('unsolved')?></option>
                        <option value="3"><?=_('solved')?></option>
                    </select><br />
                    <label for="condition-new-groupby"><?=_('Group by')?>:</label>
                    <input id="condition-new-groupby" type="text" name="conditions[new][groupby]" placeholder="<?=_('Group by')?>" value="" />
                <?php elseif($achievement['condition'] == 'achievement') : ?>
                    <label for="condition-new-field"><?=_('Field')?>:</label>
                    <select id="condition-new-field" name="conditions[new][field]">
                        <?php foreach($achievementFields as &$field) : ?>
                        <option value="<?=$field?>"><?=$field?></option>
                        <?php endforeach ?>
                    </select><br />
                    <input id="condition-new-count" type="checkbox" name="conditions[new][count]" />
                    <label for="condition-new-count"><?=_('Count')?></label><br />
                    <label for="condition-new-value"><?=_('Value')?>:</label>
                    <input id="condition-new-value" type="number" name="conditions[new][value]" placeholder="<?=_('Value')?>" value="" /><br />
                    <label for="condition-new-achievement"><?=_('Achievement')?>:</label>
                    <select id="condition-new-achievement" name="conditions[new][achievement]">
                        <option value=""><?=_('unset')?><option>
                        <?php foreach($achievements as &$a) : ?>
                        <option value="<?=$a['url']?>"><?=$a['title']?></option>
                        <?php endforeach ?>
                    </select><br />
                    <label for="condition-new-groupby"><?=_('Group by')?>:</label>
                    <input id="condition-new-groupby" type="text" name="conditions[new][groupby]" placeholder="<?=_('Group by')?>" value="" />
                <?php else : ?>
                    hallo
                <?php endif ?>
            </li>
        </ul>
    </fieldset>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>
