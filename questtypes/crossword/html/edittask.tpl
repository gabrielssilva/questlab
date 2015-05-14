<form method="post" class="crossword">
    <fieldset>
        <legend><?=_('Preview')?></legend>
        <table id="matrix">
            <tbody>
                <?php foreach(range(0, $maxY) as $y) : ?>
                <tr>
                    <?php foreach(range(0, $maxX) as $x) : ?>
                    <td>
                        <?php if(array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) : ?>
                        <?php if(count($matrix[$x][$y]['indices']) > 0) : ?><span class="index"><?=implode('/',array_map(function($e) { return $e+1; }, $matrix[$x][$y]['indices']))?></span><?php endif ?>
                        <input type="text" maxlength="1" size="1" disabled="disabled" value="<?=$matrix[$x][$y]['char']?>" />
                        <?php endif ?>
                    </td>
                    <?php endforeach ?>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table>
    </fieldset>
    <fieldset class="dev">
        <legend><?=_('Questions')?></legend>
        <ol>
            <?php foreach($words as &$word) : ?>
            <li>
                <?=_('Position')?>:
                <input type="number" value="<?=$word['pos_x']+1?>" />
                <input type="number" value="<?=$word['pos_y']+1?>" />
                <select>
                    <option <?php if(!$word['vertical']) : ?>selected="selected"<?php endif ?>><?=_('horizontal')?></option>
                    <option <?php if($word['vertical']) : ?>selected="selected"<?php endif ?>><?=_('vertical')?></option>
                </select>
                <br />
                <?=_('Question')?>:<br />
                <textarea><?=$word['question']?></textarea><br />
                <?=_('Answer')?>:<br />
                <input type="text" value="<?=$word['word']?>" />
                <br />
                <input type="button" class="remove-question" value="−" />
            </li>
            <?php endforeach ?>
            <li>
                <input type="button" class="add-question" value="+" />
            </li>
        </ol>
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>
